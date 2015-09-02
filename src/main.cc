#include "InetAddress.h"
#include "ThreadPool.h"
#include "Task.h"
#include "TcpServer.h"
#include "conf.h"
#include "MyDict.h"
#include "Cache.h"
#include "MyTimerThread.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <map>

static ThreadPool *pThreadPool = NULL;

void onConnection(const wd::TcpConnectionPtr & conn);
void onMessage(const wd::TcpConnectionPtr & conn);
void onClose(const wd::TcpConnectionPtr & conn);

int main()
{
	//读取配置文件
	std::string filepath = "/home/luo/project/spellcorrection5/conf/my.conf";
	MyConf myconf(filepath);
	bool initFlag = myconf.init();
	if(initFlag)
	{
		myconf.show();
	}

	std::map<std::string, std::string> &myMap = myconf.getMap();
	std::string dictpath = myMap["my_dict"];	
	std::string dictpath2 = myMap["my_cn_dict"];
	MyDict *pMydict = MyDict::createInstance(dictpath.c_str(), dictpath2.c_str());

	std::string cachepath = myMap["my_cache"];
	Cache cache;
	cache.read_from_file(cachepath.c_str());
	
	//初始化线程池
	ThreadPool thp(50, 10, cache, (*pMydict));
	thp.start();
	pThreadPool = &thp;

	//初始化定时器
	MyTimerThread myTmThread(1, 100, std::bind(&ThreadPool::update, &thp));
	myTmThread.start();

	//获取服务器端的ip和port
	std::string sip = myMap["my_ip"];
	std::string sport = myMap["my_port"];

	int iport = 0;//将字符串转换为整型
	std::stringstream ss(sport);
	ss >> iport;

	//创建服务器并进行监听
	wd::InetAddress inetAddr(sip, iport);
	wd::TcpServer server(inetAddr);
	server.setConnectionCallback(&onConnection);
	server.setMessageCallback(&onMessage);
	server.setCloseCallback(&onClose);
	server.start();

	return 0;
}

void onConnection(const wd::TcpConnectionPtr & conn)
{
	printf("%s has connected.\n", conn->toString().c_str());
	conn->send("hello, welcome to chat server.\n");
}

void onMessage(const wd::TcpConnectionPtr & conn)
{
	//获取客户端的信息
	std::string msg(conn->receive());
	std::string::size_type n = msg.find('\n');
	if(n != std::string::npos)
	{
		msg = msg.substr(0, n);
	}
	std::cout << "receive: " << msg << ",sizeof(msg) = " << msg.size() << std::endl;
	//conn->send(msg);
	//封装任务，并交给线程池执行任务
	Task task(msg, conn->fd(), pThreadPool->mydict_);
	pThreadPool->addTask(task);
}

void onClose(const wd::TcpConnectionPtr & conn)
{
	printf("close connection: %s.\n", conn->toString().c_str());
}

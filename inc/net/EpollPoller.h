#ifndef EPOLL_POLLER_H
#define EPOLL_POLLER_H

#include "Noncopyable.h"
#include <vector>
#include <map>
#include <sys/epoll.h>
#include "TcpConnection.h"

namespace wd
{

class EpollPoller : Noncopyable
{
public:
    typedef TcpConnection::TcpConnectionCallback EpollCallback;

    explicit EpollPoller(int listenfd);
    ~EpollPoller();

    void loop(); //启动epoll
    void unloop(); //关闭epoll

    void setConnectCallback(EpollCallback cb)
    { onConnectCallback_ = std::move(cb); }
    void setMessageCallback(EpollCallback cb)
    { onMessageCallback_ = std::move(cb); }
    void setCloseCallback(EpollCallback cb)
    { onCloseCallback_ = std::move(cb); }

private:
    void waitEpollFd(); //循环
    void handleConnection(); //处理accept
    void handleMessage(int peerfd); //处理msg


    const int epollfd_;
    const int listenfd_; 
    bool isLooping_; //是否在运行

    typedef std::vector<struct epoll_event> EventList;
    EventList events_;  //保存活跃的fd

    typedef std::map<int, TcpConnectionPtr> ConnectionList;
    ConnectionList lists_; //实现fd到conn的映射

    EpollCallback onConnectCallback_;
    EpollCallback onMessageCallback_;
    EpollCallback onCloseCallback_;
};

}//end namespace wd

#endif //EPOLL_POLLER_H

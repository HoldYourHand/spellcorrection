#ifndef _TASK_H
#define _TASK_H

#include <string>
#include <queue>
#include <set>
class Cache;
class MyDict;

struct MyResult
{
	std::string word_;
	int ifreq_;
	int idist_;
};

struct MyCompare
{
	bool operator()(const MyResult &lhs, const MyResult &rhs)
	{
		if(lhs.idist_ > rhs.idist_)
		{	return true;	}
		else if(lhs.idist_ == rhs.idist_ &&
				lhs.ifreq_ > rhs.ifreq_)
		{	return true;	}
		else if(lhs.idist_ == rhs.idist_ &&
				lhs.ifreq_ == rhs.ifreq_ &&
				lhs.word_ > rhs.word_)
		{	return true;	}
		else
			return false;
	}
};

class Task
{
public:
	Task(const std::string &expr, int sockfd, MyDict &mydict);
	Task(const char *expr, int sockfd, MyDict &mydict);

	void execute(Cache &cache);

private:
	void query_idx_table();
	void statistic(std::set<int> &iset);
	int distance(const std::string &rhs);//计算两个字符串的编辑距离
	void response(Cache &cache);

private:
	std::string expr_;
	int sockfd_;
	MyDict &mydict_;
	std::priority_queue<MyResult, std::vector<MyResult>, MyCompare> que_res_;
};

#endif

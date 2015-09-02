#include "ThreadPool.h"
//#include "MyDict.h"
#include "Task.h"
#include <iostream>
#include <fstream>
#include <string>


ThreadPool::ThreadPool(size_t queueSize, size_t threadsNum, Cache &cache, MyDict &mydict)
: empty_(mutex_),
  full_(mutex_),
  queueSize_(queueSize),
  threadsNum_(threadsNum),
  isExit_(false),
  cache_(cache),
  mydict_(mydict)
{
}

void ThreadPool::start()
{
    for(size_t ix = 0; ix != threadsNum_; ++ix)
    {
        threads_.push_back(
            std::unique_ptr<Thread>(
					new Thread(
						std::bind(&ThreadPool::runInThread, this, std::placeholders::_1),
						cache_
					)
			)
		);
    }
    for(size_t ix = 0; ix != threadsNum_; ++ix)
    {
        threads_[ix]->start();
    }
}

void ThreadPool::addTask(Task task)
{
    MutexLockGuard lock(mutex_);
    while(queue_.size() >= queueSize_)
        empty_.wait();
    //queue_.push(std::move(task));
    queue_.push(task);
    full_.notify();
}


Task ThreadPool::getTask()
{
    MutexLockGuard lock(mutex_);
    while(queue_.empty())
        full_.wait();
    Task task = queue_.front();
    queue_.pop();
    empty_.notify();
    return task;
}

void ThreadPool::runInThread(Cache& cache)
{
    while(!isExit_)
    {
        Task task(getTask());
        task.execute(cache);
    }
}

void ThreadPool::update()
{
	std::cout << "timer executing, update caches" << std::endl;
	
	for(size_t idx = 0; idx != threadsNum_; ++idx)
	{
		cache_.add_elements(threads_[idx]->get_cache());
	}

	for(size_t idx =0; idx != threadsNum_; ++idx)
	{
		threads_[idx]->get_cache().add_elements(cache_);
	}

	std::cout << "cache_.write_to_file();" << std::endl;
	std::string cachepath = "/home/luo/project/spellcorrection4/data/cache.dat";
	
	std::ofstream ofs(cachepath.c_str());
	cache_.write_to_file(ofs);
}

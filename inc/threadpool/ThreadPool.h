#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "MutexLock.h"
#include "Condition.h"
#include "Thread.h"
#include "Noncopyable.h"
#include "Cache.h"
#include <queue>
#include <vector>
#include <functional>
#include <memory>

class MyDict;
class Task;

class ThreadPool : private Noncopyable 
{
public:

    ThreadPool(size_t queueSize, size_t threadsNum, Cache &cache, MyDict &mydict);

    void start();

    void addTask(Task task);
    Task getTask();


    void runInThread(Cache &cache);

	void update();// 更新Cache

private:
    mutable MutexLock mutex_;
    Condition empty_;
    Condition full_;

    size_t queueSize_;
    std::queue<Task> queue_;

    const size_t threadsNum_;
    std::vector<std::unique_ptr<Thread> > threads_;
    bool isExit_;

	Cache  &cache_;
public:
	MyDict &mydict_;
};

#endif //THREADPOOL_H

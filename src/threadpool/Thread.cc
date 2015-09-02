#include "Thread.h"
#include "MutexLock.h"
#include <assert.h>


Thread::Thread(ThreadCallback callback, Cache &cache)
: threadId_(0),
  isRunning_(false),
  callback_(std::move(callback)),
  cache_(cache)
{
}
    
Thread::~Thread()
{
    if(isRunning_)
    {
        //detach
        TINY_CHECK(!pthread_detach(threadId_));
    }
}

void Thread::start()
{
    TINY_CHECK(!pthread_create(&threadId_, NULL, runInThread, this));
    isRunning_ = true;
}
void Thread::join()
{
    assert(isRunning_);
    TINY_CHECK(!pthread_join(threadId_, NULL));
    isRunning_ = false;
}

Cache &Thread::get_cache()
{
	return cache_;
}

void *Thread::runInThread(void *arg)
{
    Thread *pt = static_cast<Thread*>(arg);
    pt->callback_(pt->cache_); //调用回调函数

    return NULL;
}



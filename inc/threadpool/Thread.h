#ifndef THREAD_H_
#define THREAD_H_

#include <functional>
#include <pthread.h>
#include "Noncopyable.h"
#include "Cache.h"

    
class Thread : private Noncopyable 
{
public:
    typedef std::function<void (Cache &)> ThreadCallback;

    explicit Thread(ThreadCallback callback, Cache &cache);
    ~Thread();

    void start();
    void join();

	Cache &get_cache();

private:
    static void *runInThread(void *);
private:

    pthread_t threadId_;
    bool isRunning_;
    ThreadCallback callback_; //回调函数
	Cache cache_;
};

#endif //THREAD_H_

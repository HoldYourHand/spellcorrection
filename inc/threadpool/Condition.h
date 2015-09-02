#ifndef CONDITION_H_
#define CONDITION_H_

#include "Noncopyable.h"
#include <pthread.h>

class MutexLock;

class Condition : Noncopyable
{
public:
    Condition(MutexLock &mutex);
    ~Condition();

    void wait();
    void notify();
    void notifyAll();

private:
    pthread_cond_t cond_;
    MutexLock &mutex_;
};
#endif //CONDITION_H_

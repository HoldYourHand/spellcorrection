#ifndef __MYTIMERTHREAD_H__
#define __MYTIMERTHREAD_H__

#include "Timer.h"
#include "TimerThread.h"

class MyTimerThread
{
public:
	typedef std::function<void ()> Callback;

	MyTimerThread(int val, int interval, Callback cb);

	void start();
	void stop();

private:
	Timer timer_;
	TimerThread thread_;
};

#endif

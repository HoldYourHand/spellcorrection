#ifndef __TIMER_H__
#define __TIMER_H__

#include "Noncopyable.h"
#include <functional>

class Timer : Noncopyable
{
public:
	typedef std::function<void ()> Callback;
	Timer(int val, int interval, Callback cb);
	~Timer();

	void start();
	void stop();

private:
	int timerfd_;
	int val_;
	int interval_;
	Callback cb_;
	bool isStarted_;
};
#endif

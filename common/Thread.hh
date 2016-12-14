#pragma once

#include <thread>
#include "AThread.hh"

class Thread : public AThread
{
public:
	Thread();
	virtual ~Thread();
	std::thread *getThread();
	template<typename F>
	bool createThread(F threadfunc);
	virtual void join();

private:
	std::thread *_thread;
};

template<typename F>
inline bool Thread::createThread(F threadfunc)
{
	_thread = new boost::thread(threadfunc);
	return (true);
}
#pragma once

#include <thread>
#include "AThread.hh"

class Thread : public AThread
{
public:
	Thread();
	virtual ~Thread();
	std::thread *getThread() const;
	template<typename F>
	bool createThread(F threadfunc);
	virtual void join();
	virtual bool isJoinable() const;

private:
	std::thread *_thread;
};

template<typename F>
inline bool Thread::createThread(F threadfunc)
{
	_thread = new std::thread(threadfunc);
	return (true);
}

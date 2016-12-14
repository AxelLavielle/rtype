#pragma once

#include "AThreadPool.hh"
#include <thread>
#include <vector>

class ThreadPool : public AThreadPool
{
public:
	ThreadPool();
	~ThreadPool();
	virtual bool addThread(IThread *thread);
	virtual bool removeThread(IThread *thread);
	virtual void joinAll();
	virtual bool is_thread_in(IThread *thread);

private:
	std::vector<IThread *>		_threadGroup;
};

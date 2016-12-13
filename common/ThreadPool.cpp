#include "ThreadPool.hh"



Spider::ThreadPool::ThreadPool()
{
}


Spider::ThreadPool::~ThreadPool()
{
}

bool Spider::ThreadPool::addThread(IThread * thread)
{
	_threadGroup.add_thread((static_cast<Thread*>(thread))->getThread());
	_size = _threadGroup.size();
	return (true);
}

bool Spider::ThreadPool::removeThread(IThread * thread)
{
	_threadGroup.remove_thread((static_cast<Thread*>(thread))->getThread());
	_size = _threadGroup.size();
	return (true);
}

void Spider::ThreadPool::joinAll()
{
	_threadGroup.join_all();
}

void Spider::ThreadPool::interruptAll()
{
	_threadGroup.interrupt_all();
}

bool Spider::ThreadPool::is_this_thread_in()
{
	return (_threadGroup.is_this_thread_in());
}

bool Spider::ThreadPool::is_thread_in(IThread * thread)
{
	return (_threadGroup.is_thread_in((static_cast<Thread*>(thread))->getThread()));
}
	
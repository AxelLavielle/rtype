#include "Thread.hh"

Thread::Thread()
{
	_thread = NULL;
}

Thread::~Thread()
{
	delete _thread;
}

std::thread *Thread::getThread() const
{
	return (_thread);
}

void Thread::join()
{
	_thread->join();
}

bool Thread::isJoinable() const
{
	return (_thread->joinable());
}

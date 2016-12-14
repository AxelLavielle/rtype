#include "Thread.hh"



Thread::Thread()
{
	_thread = NULL;
}

Thread::~Thread()
{
}

std::thread *Thread::getThread()
{
	return (_thread);
}

void Thread::join()
{
	_thread->join();
}

#include "Thread.hh"



Spider::Thread::Thread()
{
	_thread = NULL;
}


Spider::Thread::~Thread()
{
}

boost::thread * Spider::Thread::getThread()
{
	return (_thread);
}

void Spider::Thread::join()
{
	_thread->join();
}

void Spider::Thread::interrupt()
{
	_thread->interrupt();
}
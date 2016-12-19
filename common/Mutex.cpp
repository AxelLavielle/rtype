#include "Mutex.hh"



Mutex::Mutex()
{
	_mutex = new std::mutex();
}


Mutex::~Mutex()
{
	delete _mutex;
}

void Mutex::lock()
{
	_mutex->lock();
}

void Mutex::unlock()
{
	_mutex->unlock();
}

bool Mutex::tryLock()
{
	return (_mutex->try_lock());
}
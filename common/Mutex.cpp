#include "Mutex.hh"



Mutex::Mutex()
{
}


Mutex::~Mutex()
{
}

void Mutex::lock()
{
	_mutex.lock();
}

void Mutex::unlock()
{
	_mutex.unlock();
}

bool Mutex::tryLock()
{
	return (_mutex.try_lock());
}
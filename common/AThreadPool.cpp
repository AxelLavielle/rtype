#include "AThreadPool.hh"

AThreadPool::AThreadPool()
{
	_size = 0;
}

AThreadPool::~AThreadPool()
{
}

int AThreadPool::getSize()
{
	return (_size);
}

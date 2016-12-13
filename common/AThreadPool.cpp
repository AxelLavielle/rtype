#include "AThreadPool.hh"

Spider::AThreadPool::AThreadPool()
{
	_size = 0;
}


Spider::AThreadPool::~AThreadPool()
{
}

int Spider::AThreadPool::getSize()
{
	return (_size);
}

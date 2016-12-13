#pragma once

#include <boost/thread/mutex.hpp>
#include "AMutex.hh"

class Mutex : public AMutex
{
public:
	Mutex();
	virtual ~Mutex();
	virtual void lock();
	virtual void unlock();

private:
	boost::mutex _mutex;
};


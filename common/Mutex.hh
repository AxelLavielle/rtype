#pragma once

#include <mutex>
#include "AMutex.hh"

class Mutex : public AMutex
{
public:
	Mutex();
	virtual ~Mutex();
	virtual void lock();
	virtual void unlock();
	virtual bool tryLock() const;

private:
	std::mutex *_mutex;
};


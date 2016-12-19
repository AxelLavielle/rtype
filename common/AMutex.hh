#pragma once

#include "IMutex.hpp"

class AMutex : public IMutex
{
public:
	AMutex();
	virtual ~AMutex();
	virtual void lock() = 0;
	virtual void unlock() = 0;
	virtual bool tryLock() = 0;
};


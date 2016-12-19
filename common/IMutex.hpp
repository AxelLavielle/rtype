#pragma once

class IMutex
{
public:
	virtual ~IMutex() {};
	virtual void lock() = 0;
	virtual void unlock() = 0;
	virtual bool tryLock() const = 0;
};

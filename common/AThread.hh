#pragma once

#include "IThread.hpp"

class AThread : public IThread
{
public:
	AThread();
	virtual ~AThread();
	virtual void join() = 0;
};

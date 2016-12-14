#pragma once

class IThread
{
public:
	virtual ~IThread() {};
	virtual void join() = 0;
};

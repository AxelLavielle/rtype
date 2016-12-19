#pragma once

class IThread
{
public:
	virtual ~IThread() {};
	virtual void join() = 0;
	virtual bool isJoinable() const = 0;
};

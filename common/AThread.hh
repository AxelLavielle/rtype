#pragma once

#include "IThread.hpp"

namespace Spider
{
	class AThread : public IThread
	{
	public:
		AThread();
		virtual ~AThread();
		virtual void join() = 0;
		virtual void interrupt() = 0;
	};
};
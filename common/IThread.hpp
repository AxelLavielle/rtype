#pragma once

namespace Spider
{
	class IThread
	{
	public:
		virtual ~IThread() {};
		virtual void join() = 0;
		virtual void interrupt() = 0;
	};
};
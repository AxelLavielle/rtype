#pragma once

#include <boost/thread/thread.hpp>
#include "AThread.hh"

namespace Spider
{
	class Thread : public AThread
	{
	public:
		Thread();
		virtual ~Thread();
		boost::thread *getThread();
		template<typename F>
		bool createThread(F threadfunc);
		virtual void join();
		virtual void interrupt();

	private:
		boost::thread *_thread;
	};

	template<typename F>
	inline bool Thread::createThread(F threadfunc)
	{
		_thread = new boost::thread(threadfunc);
		return (true);
	}
};
#pragma once

#include <boost/thread/thread.hpp>
#include "AThreadPool.hh"

namespace Spider
{
	class ThreadPool : public AThreadPool
	{
	public:
		ThreadPool();
		~ThreadPool();
		virtual bool addThread(IThread *thread);
		virtual bool removeThread(IThread *thread);
		virtual void joinAll();
		virtual void interruptAll();
		virtual bool is_this_thread_in();
		virtual bool is_thread_in(IThread *thread);

	private:
		boost::thread_group _threadGroup;
	};
};
#pragma once

#include "IThread.hpp"
#include <thread>
#include <vector>

class ThreadPool
{
public:
	ThreadPool();
	~ThreadPool();
	bool	addThread(IThread *thread);
	bool	removeThread(IThread *thread);
	void	joinAll();
	bool	isThreadIn(IThread *thread);
	void	deleteUnusedThread();
        int	getSize() const;


private:
	std::vector<IThread *>	_threadGroup;
	int			_size;
};

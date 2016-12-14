#include "ThreadPool.hh"

ThreadPool::ThreadPool()
{
}

ThreadPool::~ThreadPool()
{
}

bool ThreadPool::addThread(IThread * thread)
{
	_threadGroup.push_back(thread);
	_size = _threadGroup.size();
	return (true);
}

bool ThreadPool::removeThread(IThread * thread)
{
	unsigned int	i = 0;
	int				a = 0;

	while (i != _threadGroup.size())
	{
		if (_threadGroup[i] == thread)
		{
			_threadGroup.erase(_threadGroup.begin() + i);
			a++;
			break;
		}
		i++;
	}
	if (a == 0)
		return (false);
	_size = _threadGroup.size();
	return (true);
}

void ThreadPool::joinAll()
{
	unsigned int	i = 0;

	while (i != _threadGroup.size())
	{
		_threadGroup[i]->join();
		i++;
	}
}

bool ThreadPool::is_thread_in(IThread *thread)
{
	unsigned int	i = 0;

	while (i != _threadGroup.size())
	{
		if (_threadGroup[i] == thread)
			return (true);
		i++;
	}
	return (false);
}
	
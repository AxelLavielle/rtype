#include "PathFileManager.hh"



PathFileManager::PathFileManager()
{
	_root = "";
}

PathFileManager::PathFileManager(const PathFileManager & p)
{
	_root = p.getRoot();
}


PathFileManager::~PathFileManager()
{
}

bool PathFileManager::init()
{
	char	*buff;

#if !defined(__linux__) && !defined(__APPLE__)

	size_t	size;
	std::string::iterator	it;

	buff = NULL;
	size = 0;
	_dupenv_s(&buff, &size, "USERPROFILE");
	if (!buff)
		return (false);
	_root = buff;
	_root += "/henType/";
	it = _root.begin();
	while (it != _root.end())
	{
		if (*it == '\\')
			*it = '/';
		++it;
	}
#else

	buff = getenv("HOME");
	if (!buff)
		return (false);
	_root = buff;
	_root += "/.henType/";

#endif // __linux__

	return (true);
}

std::string PathFileManager::getRoot() const
{
	return _root;
}

PathFileManager &PathFileManager::operator=(const PathFileManager & p)
{
	_root = p.getRoot();
	return (*this);
}

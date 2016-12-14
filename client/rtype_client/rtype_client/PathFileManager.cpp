#include "PathFileManager.hh"



PathFileManager::PathFileManager()
{
	_root = "";
}


PathFileManager::~PathFileManager()
{
}
#include <iostream>
bool PathFileManager::init()
{
	char	*buff;

#ifndef __linux__
	
	size_t	size;

	buff = NULL;
	size = 0;
	_dupenv_s(&buff, &size, "USERPROFILE");
	if (!buff)
		return (false);
	_root = buff;
	_root += "\\";

#else

	buff = getenv("HOME");
	if (!buff)
		return (false);
	_root = buff;
	_root += "/";

#endif // __linux__

	return (true);
}

std::string PathFileManager::getRoot() const
{
	return _root;
}

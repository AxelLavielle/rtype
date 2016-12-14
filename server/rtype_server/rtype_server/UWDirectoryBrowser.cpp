#include "UWDirectoryBrowser.hh"
#include <iostream>

UWDirectoryBrowser::UWDirectoryBrowser()
{
  _dir = NULL;
  _ent = NULL;
}

UWDirectoryBrowser::~UWDirectoryBrowser()
{
 }

bool	UWDirectoryBrowser::refresh()
{
  if ((_dir = opendir(_path.c_str())))
    {
      while ((_ent = readdir(_dir)))
	{
	#ifdef __linux__
	  if (this->extIsValid(".so", _ent->d_name) && std::string(_ent->d_name).size() > 3)
	    _files.push_back(_path + "/" + _ent->d_name);
	  #elif _WIN32
	  if (this->extIsValid(".lib", _ent->d_name) && std::string(_ent->d_name).size() > 3)
	    _files.push_back(_path + "/" + _ent->d_name);
	  #endif
	}
      closedir(_dir);
      return (true);
    }
  return (false);
}
#include "UDirectoryBrowser.hh"
#include <iostream>

UDirectoryBrowser::UDirectoryBrowser()
{
  _dir = NULL;
  _ent = NULL;
}

UDirectoryBrowser::~UDirectoryBrowser()
{
  if (_dir)
    free(_dir);
  if (_ent)
    free(_ent);
}

bool	UDirectoryBrowser::refresh()
{
  this->clear();
  if ((_dir = opendir(_path.c_str())))
    {
      while ((_ent = readdir(_dir)))
	{
	  if (this->extIsValid(".so", _ent->d_name) && std::string(_ent->d_name).size() > 3)
	    _files.push_back(_path + "/" + _ent->d_name);
	}
      closedir(_dir);
      return (true);
    }
  return (false);
}

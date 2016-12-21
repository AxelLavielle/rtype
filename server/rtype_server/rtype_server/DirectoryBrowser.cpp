#include "DirectoryBrowser.hh"
#include <iostream>

DirectoryBrowser::DirectoryBrowser()
{
#ifdef __linux__
 _dir = NULL;
  _ent = NULL;
#endif
}

DirectoryBrowser::~DirectoryBrowser()
{
  _files.clear();
}

bool	DirectoryBrowser::refresh()
{
  #ifdef __linux__
  if ((_dir = opendir(_path.c_str())))
    {
      while ((_ent = readdir(_dir)) != NULL)
	{
	  if (this->extIsValid(".so", _ent->d_name) && std::string(_ent->d_name).size() > 3)
	    {
	      std::cout << _ent->d_name << std::endl;
	      _files.push_back(_path + "/" + _ent->d_name);
	    }
	}
      closedir(_dir);
      return (true);
    }
  std::cerr << "Can't open dir" << std::endl;

  #elif _WIN32
	if ((_handle = FindFirstFile(_path.c_str(), &_findFileData)) == INVALID_HANDLE_VALUE)
	{
		std::cerr << "Can't open dir" << std::endl;
		return (false);
	}
	while (FindNextFile(_handle, &_findFileData))
    {
//		std::cout << _findFileData.cFileName << std::endl;
		if (this->extIsValid(".lib", _findFileData.cFileName) && std::string(_findFileData.cFileName).size() > 3)
		  {
		    std::cout << _findFileData.cFileName << std::endl;
		    _files.push_back(_path + "/" + _findFileData.cFileName);
		  }
    }
  FindClose(_handle);
  return (true);

#endif
  return (false);
}

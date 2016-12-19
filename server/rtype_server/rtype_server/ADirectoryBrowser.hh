#pragma once

#include <vector>
#include <string>
#ifdef __linux__
#include <dirent.h>
#elif _WIN32
#include <windows.h>
#endif
#include "IDirectoryBrowser.hpp"

class ADirectoryBrowser
  : public IDirectoryBrowser
{
protected:
  std::vector<std::string>	_files;
  std::string			_path;
  #ifdef __linux__
  DIR				*_dir;
  struct dirent			*_ent;
  #elif _WIN32
  WIN32_FIND_DATA		_findFileData;
  HANDLE			_handle;
  #endif
public:
  ADirectoryBrowser();
  virtual ~ADirectoryBrowser();

  virtual bool				refresh() = 0;
  virtual bool				setPath(const std::string &);
  virtual bool				extIsValid(const std::string &, const std::string &);
  virtual void				dump();
  virtual void				clear();
  virtual std::vector<std::string>	getFiles() const;
};

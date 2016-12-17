#pragma once

#include <vector>
#include <string>
#include <dirent.h>
#include "IDirectoryBrowser.hpp"

class ADirectoryBrowser
  : public IDirectoryBrowser
{
protected:
  std::vector<std::string>	_files;
  std::string			_path;
  DIR				*_dir;
  struct dirent			*_ent;
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

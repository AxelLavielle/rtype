#pragma once

#include <vector>
#include <string>
#include <dirent.h>
#include "IDirectoryBrowser.hpp"

class ADirectoryBrowser
  : public IDirectoryBrowser
{
public:
  ADirectoryBrowser();
  virtual ~ADirectoryBrowser();
  virtual bool refresh();
  bool		setPath(const std::string &);
  void		clear();
  bool		extIsValid(const std::string &, const std::string &);
  void		dump();
  const std::vector<std::string>	&getFiles() const;
protected:
  std::vector<std::string>	_files;
  std::string			_path;
  DIR				*_dir;
  struct dirent			*_ent;
};

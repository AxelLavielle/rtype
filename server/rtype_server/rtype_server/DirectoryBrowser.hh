#pragma once

#include <vector>
#include <string>
#include <dirent.h>

class DirectoryBrowser
{
public:
  DirectoryBrowser();
  ~DirectoryBrowser();
  bool		setPath(const std::string &);
  void		clear();
  bool		refresh();
private:
  std::vector<std::string>	_files;
  std::string			_path;
  DIR				*_dir;
  struct dirent			*_ent;
};

#pragma once

#include <string>

class IDirectoryBrowser
{
public:
  virtual	~IDirectoryBrowser(){}
  virtual	bool refresh() = 0;
  virtual	bool setPath(const std::string &) = 0;
  virtual	bool extIsValid(const std::string&, const std::string &) = 0;
  virtual	void dump() = 0;
  virtual	void clear() = 0;
  virtual	const std::vector<std::string>	&getFiles() const  = 0;
};

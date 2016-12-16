#include "ADirectoryBrowser.hh"
#include <iostream>

ADirectoryBrowser::ADirectoryBrowser()
{
}

ADirectoryBrowser::~ADirectoryBrowser()
{
}

bool	ADirectoryBrowser::setPath(const std::string &path)
{
  _path = path;
  return (true);
}

void	ADirectoryBrowser::clear()
{
  _files.clear();
}

bool	ADirectoryBrowser::extIsValid(const std::string &ext, const std::string &toCheck)
{
  std::size_t found = toCheck.find(ext);
  return (found + ext.size() == toCheck.size());
}

void	ADirectoryBrowser::dump()
{
  for (std::vector<std::string>::iterator it = _files.begin(); it != _files.end(); it++)
    {
      std::cout << *it << std::endl;
    }
}

std::vector<std::string>	ADirectoryBrowser::getFiles() const
{
  return (_files);
}

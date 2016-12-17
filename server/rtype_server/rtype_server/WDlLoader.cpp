#include "WDlLoader.hh"

WDlLoader::WDlLoader()
{
}

WDlLoader::~WDlLoader()
{
  // TODO equivalent
  // if (_dlHandle)
  //   dlclose(_dlHandle);

}

IEntity		*WDlLoader::getInstance()
{
  return (NULL);
}

bool		WDlLoader::load(const std::string &path)
{
  (void)path;
  return (true);
}

bool		WDlLoader::refresh()
{
  return (true);
}

#include "WDlLoader.hh"

WDlLoader::WDlLoader()
{
}

WDlLoader::~WDlLoader()
{
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

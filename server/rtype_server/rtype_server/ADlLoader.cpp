#include "ADlLoader.hh"

ADlLoader::ADlLoader() : _dlHandle(NULL)
{
}

ADlLoader::~ADlLoader()
{
}

void		*ADlLoader::getHandle()
{
  return (_dlHandle);
}

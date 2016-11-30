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

bool		ADlLoader::closeHandle()
{
  if (_dlHandle)
    {
      dlclose(_dlHandle);
      _dlHandle = NULL;
      return (true);
    }
  return (false);
}

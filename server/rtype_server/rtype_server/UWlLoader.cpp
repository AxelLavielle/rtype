#include "UWDlLoader.hh"
#include <iostream>

UWDlLoader::UWDlLoader()
{
}

UWDlLoader::~UWDlLoader()
{
  dlclose(_dlHandle);
  _dlHandle = NULL;
}

IEntity	*UWDlLoader::getInstance(void)
{
  IEntity		*(*Entity)();

  Entity = reinterpret_cast<IEntity*(*)()>(dlsym(_dlHandle, "createEntity"));
  if (Entity == NULL)
    std::cout << "ERROR " << std::endl;
  IEntity	*rtn = Entity();
  std::cout << rtn->getName() << std::endl;
  return (rtn);
}

bool	UWDlLoader::load(const std::string &path)
{
  _dlHandle = dlopen(path.c_str(), RTLD_LAZY | RTLD_NOW);
  if (_dlHandle == NULL)
    std::cout << dlerror() << std::endl;
  return (_dlHandle != NULL);
}

bool	UWDlLoader::refresh()
{
  return (true);
}

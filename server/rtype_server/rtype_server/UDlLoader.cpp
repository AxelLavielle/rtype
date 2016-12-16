#include "UDlLoader.hh"
#include <iostream>

UDlLoader::UDlLoader()
{
}

UDlLoader::~UDlLoader()
{
  if (_dlHandle)
    dlclose(_dlHandle);
}

IEntity		*UDlLoader::getInstance()
{
  IEntity	*(*Entity)();

  Entity = reinterpret_cast<IEntity*(*)()>(dlsym(_dlHandle, "createEntity"));
  if (Entity == NULL)
    std::cout << "ERROR " << std::endl;
  IEntity	*rtn = Entity();
  std::cout << rtn->getName() << std::endl;
  return (rtn);
}

bool		UDlLoader::load(const std::string &path)
{
  _dlHandle = dlopen(path.c_str(), RTLD_LAZY | RTLD_NOW);
  if (_dlHandle == NULL)
    std::cout << dlerror() << std::endl;
  return (_dlHandle != NULL);
}

bool		UDlLoader::refresh()
{
  return (true);
}

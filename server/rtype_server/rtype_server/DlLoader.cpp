#include "DlLoader.hh"
#include <iostream>

DlLoader::DlLoader()
{
}

DlLoader::~DlLoader()
{
#ifdef __linux__
  if (_dlHandle)
    dlclose(_dlHandle);
#endif
}

typedef IEntity *(__stdcall *f_funci)();

IEntity		*DlLoader::getInstance()
{
  //IEntity	*(*Entity)();
	f_funci Entity;

  #ifdef __linux__
  Entity = reinterpret_cast<IEntity*(*)()>(dlsym(_dlHandle, "createEntity"));
#elif _WIN32
//  Entity = (lpfnDllFunc1)(GetProcAddress((HINSTANCE)_dlHandle, "createEntity"));
  //Entity = reinterpret_cast<IEntity* (*)()>(GetProcAddress((HINSTANCE)_dlHandle, "createEntity"));
  //Entity = (f_funci)(GetProcAddress((HINSTANCE)_dlHandle, "createEntity"));

	Entity = (f_funci)GetProcAddress((HINSTANCE)_dlHandle, "createEntity");

#endif
  if (Entity == NULL)
    {
      std::cout << "Error in getInstance" << std::endl;
	  std::cout << GetLastError() << std::endl;
      return (NULL);
    }
  else
	  std::cout << "getInstance OK " << std::endl;
  IEntity	*rtn = Entity();
  return (rtn);
}

bool		DlLoader::load(const std::string &path)
{
  #ifdef __linux__
  _dlHandle = dlopen(path.c_str(), RTLD_LAZY | RTLD_NOW);
  if (_dlHandle == NULL)
    std::cout << dlerror() << std::endl;
  return (_dlHandle != NULL);
  #elif _WIN32
	_dlHandle = (void*)LoadLibrary(path.c_str());
	  if (_dlHandle == NULL)
	  {
		  std::cout << "Cannot load library" << std::endl;
		  std::cout << GetLastError() << std::endl;
	  }
#endif

  return (_dlHandle != NULL);
}

bool		DlLoader::refresh()
{
  return (this->load(_dlPath));
}

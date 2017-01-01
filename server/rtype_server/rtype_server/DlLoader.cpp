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

IEntity			*DlLoader::getInstance()
{
	createFunc	func;

	#ifdef __linux__
		Entity = reinterpret_cast<IEntity*(*)()>(dlsym(_dlHandle, "createEntity"));
	#elif _WIN32
		func = reinterpret_cast<createFunc>(GetProcAddress((HINSTANCE)_dlHandle, "createEntity"));
	#endif

	if (func == NULL)
    {
      std::cerr << "Error in getInstance" << std::endl;
	  return (NULL);
    }

  IEntity	*rtn = func();
  return (rtn);
}

bool		DlLoader::load(const std::string &path)
{
	#ifdef __linux__
		_dlHandle = dlopen(path.c_str(), RTLD_LAZY | RTLD_NOW);
		if (_dlHandle == NULL)
			std::cerr << dlerror() << std::endl;
	#elif _WIN32
		_dlHandle = (void*)LoadLibrary(path.c_str());
		if (_dlHandle == NULL)
		  std::cerr << "Cannot load library : " << GetLastError() << std::endl;
	#endif
  return (_dlHandle != NULL);
}

bool		DlLoader::refresh()
{
  return (this->load(_dlPath));
}

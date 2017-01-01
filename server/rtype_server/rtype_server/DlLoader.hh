#pragma once

# include "ADlLoader.hh"
# ifdef __linux__
# include <dlfcn.h>
# elif _WIN32
# include <windows.h>
#endif

typedef IEntity *(__stdcall *createFunc)();

class DlLoader : public ADlLoader
{
public:
  DlLoader();
  virtual ~DlLoader();

  virtual IEntity	*getInstance();
  virtual bool		load(const std::string &path);
  virtual bool		refresh();
};

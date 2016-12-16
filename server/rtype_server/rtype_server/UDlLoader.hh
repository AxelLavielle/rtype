#pragma once

# include "ADlLoader.hh"
# include <dlfcn.h>

class UDlLoader : public ADlLoader
{
public:
  UDlLoader();
  virtual ~UDlLoader();

  virtual IEntity	*getInstance();
  virtual bool		load(const std::string &path);
  virtual bool		refresh();
};

#pragma once

#include "ADlLoader.hh"

class UWDlLoader : public ADlLoader
{
public:
  UWDlLoader();
  virtual ~UWDlLoader();
  virtual IEntity	*getInstance(void);
  virtual bool		load(const std::string &path);
  virtual bool		refresh();
};

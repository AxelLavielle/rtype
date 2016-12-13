#pragma once

#include "ADlLoader.hh"

class UDlLoader : public ADlLoader
{
public:
  UDlLoader();
  virtual ~UDlLoader();
  virtual IEntity	*getInstance(void);
  virtual bool		load(const std::string &path);
  virtual bool		refresh();
};

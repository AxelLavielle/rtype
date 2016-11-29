#pragma once

#include "ADlLoader.hh"

class WDlLoader : public ADlLoader
{
public:
  WDlLoader();
  virtual ~WDlLoader();

  virtual IEntity	*getInstance(void);
  virtual bool		load(const std::string &);
};

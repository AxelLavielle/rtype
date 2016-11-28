#pragma once

#include "ADlLoader.hh"

class WDlLoader : public ADlLoader
{
public:
  WDlLoader();
  ~WDlLoader();

  IEntity	getInstance(void);
  bool		load(const std::string &);
};

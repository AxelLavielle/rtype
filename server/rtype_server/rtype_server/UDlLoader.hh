#pragma once

#include "ADlLoader.hh"

class UDlLoader : public ADlLoader
{
public:
  UDlLoader();
  ~UDlLoader();
  IEnity	getInstance(void);
  bool		load(const std::string &path);
};

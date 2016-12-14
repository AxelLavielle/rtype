#pragma once

#include "ADirectoryBrowser.hh"
#include <cstdlib>

class UWDirectoryBrowser
  : public ADirectoryBrowser
{
public:
  UWDirectoryBrowser();
  virtual ~UWDirectoryBrowser();
  virtual bool refresh();
};

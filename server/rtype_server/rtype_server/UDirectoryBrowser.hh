#pragma once

#include "ADirectoryBrowser.hh"
#include <cstdlib>

class UDirectoryBrowser
  : public ADirectoryBrowser
{
public:
  UDirectoryBrowser();
  virtual ~UDirectoryBrowser();
  virtual bool refresh();
};

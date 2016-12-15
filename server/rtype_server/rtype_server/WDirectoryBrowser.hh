#pragma once

#include "ADirectoryBrowser.hh"
#include <cstdlib>

class WDirectoryBrowser
  : public ADirectoryBrowser
{
public:
  WDirectoryBrowser();
  virtual ~WDirectoryBrowser();
  virtual bool refresh();
};

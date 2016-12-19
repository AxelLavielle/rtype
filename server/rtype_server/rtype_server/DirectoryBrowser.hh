#pragma once

#include "ADirectoryBrowser.hh"
#include <cstdlib>

class DirectoryBrowser
  : public ADirectoryBrowser
{
public:
  DirectoryBrowser();
  virtual ~DirectoryBrowser();
  virtual bool refresh();
};

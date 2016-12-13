#include "DlManager.hh"
#include <iostream>
#include "UDirectoryBrowser.hh"

int		main()
{
  DlManager	DM;

  DM.setFolderPath("./entities");
  DM.getBrowser()->dump();
  DM.setFolderPath(".");
  DM.getBrowser()->dump();
 return (0);
}

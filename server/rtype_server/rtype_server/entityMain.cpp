#include "DlManager.hh"
#include <iostream>

int		main()
{
  DlManager	DM;
  DM.setFolderPath("./entities");


  IEntity *testt = DM.getdl("Player1");
  if (testt)
    std::cout << "get " << testt->getName() << std::endl;
  return (0);
}

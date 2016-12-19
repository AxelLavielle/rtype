#include "DlManager.hh"
#include <iostream>

int		main()
{
  DlManager	DM;
  DM.setFolderPath("../../../common/entities");

  IEntity	*test = DM.getdl("Player1");
  std::cout << test->getName() << std::endl;
  return (0);
}

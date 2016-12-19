#include "DlManager.hh"
#include <iostream>
#include "IEntity.hpp"

int		main()
{
  DlManager	DM;
  DM.setFolderPath("C:/Users/Mohamad/Desktop/rtype/common/entities");

  IEntity *testt = DM.getdl("Player1");
  if (testt)
    std::cout << "get " << testt->getName() << std::endl;
  else
  {
	  std::cout << "bite" << std::endl;
  }
	while (1);
//  DM.setFolderPath("../../../common/entities");
//
//  IEntity	*test = DM.getdl("Player1");
//  std::cout << test->getName() << std::endl;
  return (0);
}

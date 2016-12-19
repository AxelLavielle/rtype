#include <stdio.h>
#include "Client.hh"
#include "SocketClientTCP.hh"
#include "SocketClientUDP.hh"
//#include "ChatInfoCmd.hh"
// #include "Serialize.hh"

int		main()
{
  //ICommand *bite = new ChatInfoCmd();

  //Serialize s;
  //char		*data;

  //bite->setCommandArg("bitas");
  //std::cout << "bite = " << bite->getCommandArg() << " " << bite->getCommandName() << std::endl << " = bite" << std::endl;
  //data = s.serialize(bite);
  //std::cout << "data = " << data << std::endl << " = data" << std::endl;
  //bite = s.unserializeCommand(data);
  //if (bite != NULL)
  //	std::cout << "bite = " << bite->getCommandArg() << " " << bite->getCommandName() << std::endl << std::endl;
  //while (1);
  //SocketClientTCP *sock = new SocketClientTCP();
  //char	*rec = NULL;
  //std::string msg;

  //sock->init("127.0.0.1", 4242);
  //sock->connectToServer();
  //while (1)
  //{
  //	std::cin >> msg;
  //	sock->sendData(msg.c_str());
  //}
  //while (1)
  //  {
  //    while ((rec = sock->receiveData()) == NULL);
  //    std::cout << rec << std::endl;
  //  }
  //sock->closure();
  //while (35);


  // SocketClientUDP *sock = new SocketClientUDP();
  // char	*rec = NULL;
  // std::string msg;

  // sock->init("127.0.0.1", 4242);
  // sock->connectToServer();
  // while (1)
  // {
  // 	std::cin >> msg;
  // 	sock->sendData(msg.c_str());
  // }
  // while (1)
  // {
  // 	while ((rec = sock->receiveData()) == NULL);
  // 	std::cout << rec << std::endl;
  // }
  // sock->closure();
  // while (35);

  Client client;

  client.launch();
  return (0);
}

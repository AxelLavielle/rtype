#include <stdio.h>
#include "Client.hh"
#include "SocketClientTCP.hh"
#include "SocketClientUDP.hh"

int		main()
{
  Client client;

  client.launch();
  return (0);
}

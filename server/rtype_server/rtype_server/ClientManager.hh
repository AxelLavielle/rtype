#pragma once

#include <vector>
#include "SocketServerTCP.hh"
#include "ServerClient.hh"

class ClientManager
{
private:
	std::vector<ServerClient *>		_clientList;

public:
	ClientManager();
	~ClientManager();
	void							addClient(int);
	std::vector<int>				getClientsTCPSockets();
	std::vector<ServerClient *>		&getClients();
	void							addDataToSend(int, const char *, int);
	void							checkDisconnectedClients();
};


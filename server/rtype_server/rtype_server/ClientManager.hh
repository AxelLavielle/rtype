#pragma once

#include "ServerClient.hh"
#include "RoomManager.hh"

class ClientManager
{
private:
	std::vector<ServerClient *>		_clientList;

public:
	ClientManager();
	~ClientManager();
	void							addClient(int);
	void							removeClient(ServerClient *);
	std::vector<int>				getClientsTCPSockets();
	std::vector<int>				getClientsUDPSockets();
	std::vector<ServerClient *>		&getClients();
	void							addDataToSend(int, const char *, int);
	void							checkDisconnectedClients(RoomManager &);
};


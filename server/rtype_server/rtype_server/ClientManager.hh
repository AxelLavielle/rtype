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
	void							addClient(int, SocketAddress *);
	void							removeClient(ServerClient *);
	std::vector<int>				getClientsTCPSockets();
	std::vector<int>				getClientsUDPSockets();
	std::vector<ServerClient *>		&getClients();
	ServerClient					*getClientByTCP(const int);
	void							addDataToSendTCP(int, const char *, int);
	void							addDataToSendUDP(int, const char *, int);
	void							checkDisconnectedClients(RoomManager &);
};


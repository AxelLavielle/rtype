#include "ClientManager.hh"

ClientManager::ClientManager()
{
}


ClientManager::~ClientManager()
{
}

void				ClientManager::addClient(const int clientSocketId, SocketAddress *addr)
{
	_clientList.push_back(new ServerClient(clientSocketId, addr));
}

void										ClientManager::removeClient(ServerClient *client)
{
	std::vector<ServerClient *>::iterator	it;

	it = _clientList.begin();
	while (it != _clientList.end())
	{
		if ((*it) == client)
		{
			_clientList.erase(it);
			return;
		}
		it++;
	}
}

std::vector<int>							ClientManager::getClientsTCPSockets()
{
	std::vector<int>						vectClientsSockets;
	std::vector<ServerClient *>::iterator	it;

	it = _clientList.begin();
	while (it != _clientList.end())
	{
		vectClientsSockets.push_back((*it)->getTCPSocket());
		it++;
	}
	return (vectClientsSockets);
}

std::vector<ServerClient *>	&ClientManager::getClients()
{
	return (_clientList);
}

ServerClient *ClientManager::getClientByTCP(const int tcpSocket)
{
	std::vector<ServerClient *>::iterator it;

	it = _clientList.begin();
	while (it != _clientList.end())
	{
		if ((*it)->getTCPSocket() == tcpSocket)
			return (*it);
		it++;
	}
	return (NULL);
}

void						ClientManager::addDataToSendTCP(int clientSocket, const char *data, int dataLen)
{
  (void)dataLen;
	std::vector<ServerClient *>::iterator it;

	it = _clientList.begin();
	while (it != _clientList.end())
	{
		if ((*it)->getTCPSocket() == clientSocket)
			(*it)->addTCPDataToSend(data);
		it++;
	}
}

void						ClientManager::addDataToSendUDP(int clientSocket, const char *data, int dataLen)
{
  (void)dataLen;
	std::vector<ServerClient *>::iterator it;

	it = _clientList.begin();
	while (it != _clientList.end())
	{
		if ((*it)->getTCPSocket() == clientSocket)
			(*it)->addUDPDataToSend(data);
		it++;
	}
}

void										ClientManager::checkDisconnectedClients(RoomManager &roomManager)
{
	std::vector<ServerClient *>::iterator	it;

	it = _clientList.begin();
	while (it != _clientList.end())
	{
		if ((*it)->isDisconnectedTCP())
		{
			if (DEBUG_MSG)
				std::cout << "################## ERASE TCP: " << (*it)->getTCPSocket() << " !!!" << std::endl;
			if ((*it)->getCurrentRoom() != -1)
				roomManager.getRoomById((*it)->getCurrentRoom())->removeClient((*it));
			it = _clientList.erase(it);
		}
		else
			it++;
	}
}

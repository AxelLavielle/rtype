#include "ClientManager.hh"

ClientManager::ClientManager()
{
}


ClientManager::~ClientManager()
{
}

void				ClientManager::addClient(int clientSocketId)
{
	_clientList.push_back(new ServerClient(clientSocketId));
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

std::vector<int>							ClientManager::getClientsUDPSockets()
{
	std::vector<int>						vectClientsSockets;
	/*std::vector<ServerClient *>::iterator	it;

	it = _clientList.begin();
	while (it != _clientList.end())
	{
		if ((*it)->getUDPSocket() != -1)
		{
			std::cout << "Add UDP Socket " << (*it)->getUDPSocket() << std::endl;
			vectClientsSockets.push_back((*it)->getUDPSocket());
		}
			
		it++;
	}*/
	return (vectClientsSockets);
}


std::vector<ServerClient *>	&ClientManager::getClients()
{
	return (_clientList);
}

ServerClient * ClientManager::getClientByTCP(const int tcpSocket)
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
	std::vector<ServerClient *>::iterator it;

	it = _clientList.begin();
	while (it != _clientList.end())
	{
		if ((*it)->getTCPSocket() == clientSocket)
			(*it)->addTCPDataToSend(data, dataLen);
		it++;
	}
}

void						ClientManager::addDataToSendUDP(int clientSocket, const char *data, int dataLen)
{
	std::vector<ServerClient *>::iterator it;

	it = _clientList.begin();
	while (it != _clientList.end())
	{
		if ((*it)->getTCPSocket() == clientSocket)
			(*it)->addUDPDataToSend(data, dataLen);
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
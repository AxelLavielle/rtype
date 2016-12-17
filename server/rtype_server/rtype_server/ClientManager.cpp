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
	std::vector<ServerClient *>::iterator	it;

	it = _clientList.begin();
	while (it != _clientList.end())
	{
		if ((*it)->getUDPSocket() != -1)
			vectClientsSockets.push_back((*it)->getUDPSocket());
		it++;
	}
	return (vectClientsSockets);
}


std::vector<ServerClient *>	&ClientManager::getClients()
{
	return (_clientList);
}

void						ClientManager::addDataToSend(int clientSocket, const char *data, int dataLen)
{
	std::vector<ServerClient *>::iterator it;

	it = _clientList.begin();
	while (it != _clientList.end())
	{
		if ((*it)->getTCPSocket() == clientSocket)
			(*it)->addDataToSend(data, dataLen);
		it++;
	}
}

void		ClientManager::checkDisconnectedClients(RoomManager &roomManager)
{
	std::vector<ServerClient *>::iterator it;

	it = _clientList.begin();
	while (it != _clientList.end())
	{
		if ((*it)->isDisconnectedTCP())
		{
			if (DEBUG_MSG)
				std::cout << "################## ERASE TCP: " << (*it)->getTCPSocket() << " !!!" << std::endl;
			if ((*it)->getCurrentRoom() != -1)
				roomManager.getRoomById((*it)->getCurrentRoom()).removeClient((*it));
			it = _clientList.erase(it);
		}
		else if ((*it)->isDisconnectedUDP())
		{
			if (DEBUG_MSG)
				std::cout << "################## ERASE UDP: " << (*it)->getUDPSocket() << " !!!" << std::endl;
			(*it)->resetUDPSocket();
		}
		else
			it++;
	}
}
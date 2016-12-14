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

std::vector<int>						ClientManager::getClientsTCPSockets()
{
	std::vector<int>					vectClientsSockets;
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

void		ClientManager::checkDisconnectedClients()
{
	std::vector<ServerClient *>::iterator it;

	it = _clientList.begin();
	while (it != _clientList.end())
	{
		if ((*it)->isDisconnected())
		{
			if (DEBUG_MSG)
				std::cout << "################## ERASE " << (*it)->getTCPSocket() << " !!!" << std::endl;
			it = _clientList.erase(it);
		}
		else
			it++;
	}
}
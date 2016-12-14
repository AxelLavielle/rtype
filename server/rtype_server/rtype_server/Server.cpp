#include "Server.hh"

Server::Server()
{
}

Server::~Server()
{
}

bool	Server::init()
{
	_socketServer = new SocketServerTCP();

	if (_socketServer->init("127.0.0.1", 4242) == false
		|| _socketServer->launch() == false)
	{
		std::cerr << "Initialization FAILED" << std::endl;
		return (false);
	}
	return (true);
}

void	Server::processMsg(const std::vector<ClientMsg> &vectMsg)
{
	std::vector<ClientMsg>::const_iterator it;

	it = vectMsg.begin();
	while (it != vectMsg.end())
	{
		if (DEBUG_MSG)
			std::cout << "Client {" << (*it).first->getTCPSocket() << "} Received : [" << (*it).second << "]" << std::endl;
		_clientManager.addDataToSend((*it).first->getTCPSocket(), "Ok\n", 3);
		it++;
	}
}

bool	Server::launch()
{
	std::vector<int>			socketsClients;
	int							clientSocketID = INVALID_SOCKET;
	std::vector<ClientMsg>		vectMsg;
	
	while (42)
	{
		std::cout << "Bla bla" << std::endl;
		_socketServer->selectFds(_clientManager.getClientsTCPSockets());

		if ((clientSocketID = _socketServer->acceptNewClient()) != -1)
		{
			_clientManager.addClient(clientSocketID);
			_clientManager.addDataToSend(clientSocketID, "Hello\n", 6);
		}
		
		vectMsg = _socketServer->receiveData(_clientManager.getClients());
		processMsg(vectMsg);
		_clientManager.checkDisconnectedClients();
		
		_socketServer->sendAllData(_clientManager.getClients());
		_clientManager.checkDisconnectedClients();
	}
	return (true);
}
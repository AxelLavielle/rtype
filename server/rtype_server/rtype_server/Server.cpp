#include "Server.hh"

Server::Server() : _cmdManager(&_clientManager, &_roomManager)
{
	_acknowledgementNumber = 42;
}

Server::~Server()
{
}

bool	Server::init()
{
	if (_socketServerTCP.init("127.0.0.1", 23737) == false
		|| _socketServerTCP.launch() == false)
	{
		std::cerr << "Initialization FAILED" << std::endl;
		return (false);
	}
	return (true);
}

void										Server::processMsg(const std::vector<ClientMsg> &vectMsg)
{
	std::vector<ClientMsg>::const_iterator	it;
	std::string								msg;
	
	it = vectMsg.begin();
	while (it != vectMsg.end())
	{
		if (DEBUG_MSG)
			std::cout << "Client {" << (*it).first->getTCPSocket() << "} Sent : [" << (*it).second << "]" << std::endl;
		
		if ((*it).second.compare(0, 4, "SYN ") == 0) // SYN_HANDSHAKE
			_cmdManager.cmdHandshakeSyn((*it).first, (*it).second, _acknowledgementNumber);
		else if ((*it).second.compare(0, 4, "ACK ") == 0) // ACK_HANDSHAKE
			_cmdManager.cmdHandshakeAck((*it).first, (*it).second, _acknowledgementNumber);
		else if ((*it).first->isLogged())
		{
			if ((*it).second.compare(0, 5, "room ") == 0) // CREATE ROOM
			{
				_cmdManager.cmdCreateRoom((*it).first, (*it).second);
			}
			if ((*it).second.compare("roomlist\n") == 0) // GET_ROOM_LIST
			{
				_cmdManager.cmdListRoom((*it).first, (*it).second);
			}
			if ((*it).second.compare(0, 4, "join") == 0) // JOIN_ROOM
			{
				_cmdManager.cmdJoinRoom((*it).first, (*it).second);
			}
		}
		_clientManager.addDataToSend((*it).first->getTCPSocket(), "Ok\n", 3);
		it++;
	}
}

bool							Server::launch()
{
	std::vector<int>			socketsClients;
	int							clientSocketID = INVALID_SOCKET;
	std::vector<ClientMsg>		vectMsg;
	
	while (42)
	{
		_socketServerTCP.selectFds(_clientManager.getClientsTCPSockets());

		if ((clientSocketID = _socketServerTCP.acceptNewClient()) != -1)
		{
			_clientManager.addClient(clientSocketID);
		}

		vectMsg = _socketServerTCP.receiveData(_clientManager.getClients());
		processMsg(vectMsg);
		_clientManager.checkDisconnectedClients();

		_socketServerTCP.sendAllData(_clientManager.getClients());
		_clientManager.checkDisconnectedClients();
	}
	return (true);
}

bool							Server::launchUDP()
{
	std::vector<int>			socketsClients;
	int							clientSocketID = INVALID_SOCKET;
	std::vector<ClientMsg>		vectMsg;
	struct sockaddr_in			clientAddr;

	while (42)
	{
		_socketServerUDP.selectFds(_clientManager.getClientsUDPSockets());

		if ((clientSocketID = _socketServerUDP.acceptNewClient(&clientAddr)) != -1)
		{
			_clientManager.addClient(clientSocketID);
			_clientManager.addDataToSend(clientSocketID, "Hello\n", 6);
		}

		vectMsg = _socketServerUDP.receiveData(_clientManager.getClients());
		processMsg(vectMsg);
		_clientManager.checkDisconnectedClients();

		_socketServerUDP.sendAllData(_clientManager.getClients());
		_clientManager.checkDisconnectedClients();
	}
	return (true);
}

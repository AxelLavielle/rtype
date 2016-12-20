#include "Server.hh"

Server::Server() : _cmdManager(&_clientManager, &_roomManager)
{
	_acknowledgementNumber = 666;
	_mutex = new Mutex();
	_cmdManager.setMutex(_mutex);
}

Server::~Server()
{
}

bool	Server::init()
{
	if (_socketServerTCP.init("127.0.0.1", 42000) == false
		|| _socketServerTCP.launch() == false
		|| _socketServerUDP.init("127.0.0.1", 9999) == false
		|| _socketServerUDP.launch() == false)
	{
		std::cerr << "Initialization FAILED" << std::endl;
		return (false);
	}
	return (true);
}

void										Server::processBasicCmd(ServerClient *client, BasicCmd *cmd)
{
	std::cout << "BASIC CMD" << std::endl;

	std::cout << "Command TYPE = " << cmd->getCommandType() << std::endl;
	switch (cmd->getCommandType())
	{
	case HANDSHAKE_SYN:
		std::cout << "---------> HANDSHAKE SYN" << std::endl;
		_cmdManager.cmdHandshakeSyn(client, cmd, _acknowledgementNumber);
		break;

	case HANDSHAKE_ACK:
		std::cout << "---------> HANDSHAKE ACK" << std::endl;
		_cmdManager.cmdHandshakeAck(client, cmd, _acknowledgementNumber);
		break;

	case GET_ROOM_LIST:
		std::cout << "---------> GET ROOM LIST" << std::endl;
		_cmdManager.cmdListRoom(client, cmd);
		break;

	case JOIN_ROOM:
		std::cout << "---------> JOIN ROOM" << std::endl;
		_cmdManager.cmdJoinRoom(client, cmd);
		break;

	case LEAVE_ROOM:
		std::cout << "---------> LEAVE ROOM" << std::endl;
		_cmdManager.cmdLeaveRoom(client, cmd);
		break;

	case CREATE_ROOM:
		std::cout << "---------> CREATE ROOM" << std::endl;
		_cmdManager.cmdCreateRoom(client, cmd);
		break;

	case SET_STATUS:
		std::cout << "---------> SET STATUS" << std::endl;
		_cmdManager.cmdSetStatus(client, cmd);
		break;

	case GET_ROOM:
		std::cout << "---------> GET ROOM" << std::endl;
		_cmdManager.cmdRoomInfo(client, cmd);
		break;

	default:
		break;
	}
}

void										Server::processMsg(const std::vector<ClientMsg> &vectMsg)
{
	std::vector<ClientMsg>::const_iterator	it;
	std::string								msg;
	
	it = vectMsg.begin();
	while (it != vectMsg.end())
	{
		std::cout << "[ProcessMsg] cmdType :" << (*it).second->getCommandName() << std::endl;
		switch ((*it).second->getCommandName())
		{
		case BASIC_CMD:
			processBasicCmd((*it).first, reinterpret_cast<BasicCmd *>((*it).second));
			break;
		default:
			std::cout << "NO CMD" << std::endl;
			break;
		}
		std::cout << "End Processing" << std::endl;
		it++;
	}
}

void							Server::processGames()
{
	std::vector<Room>			roomsReady;
	std::vector<Room>::iterator	it;

	//std::cout << "Process Games" << std::endl;
	_mutex->lock();
	roomsReady = _roomManager.getRoomsReady();
	_mutex->unlock();
	if (roomsReady.size() == 0)
		return;
	it = roomsReady.begin();
	while (it != roomsReady.end())
	{
		//std::cout << "Room [" << (*it).getName() << "] is READY" << std::endl;
		_cmdManager.cmdLaunchGame((*it).getClients(), (*it).getId());
		it++;
	}
	
}

bool							Server::launch()
{
	Thread						threadTCP;
	Thread						threadUDP;

	_roomManager.addRoom("Mio");
	_roomManager.addRoom("Mao");
	_roomManager.addRoom("Lalalalala");

	threadTCP.createThread(std::bind(&Server::TCPLoop, this));
	threadUDP.createThread(std::bind(&Server::UDPLoop, this));
	_pool.addThread(&threadTCP);
	_pool.addThread(&threadUDP);

	while (42)
	{
		processGames();
	}

	_pool.joinAll();
	return (true);
}

bool							Server::TCPLoop()
{
	std::vector<int>			socketsClients;
	int							clientSocketID = INVALID_SOCKET;
	std::vector<ClientMsg>		vectMsg;
	
	while (42)
	{
		_mutex->lock();
		_socketServerTCP.selectFds(_clientManager.getClientsTCPSockets());
		_mutex->unlock();

		if ((clientSocketID = _socketServerTCP.acceptNewClient()) != -1)
		{
			_mutex->lock();
			_clientManager.addClient(clientSocketID);
			_mutex->unlock();
		}

		_mutex->lock();
		vectMsg = _socketServerTCP.receiveData(_clientManager.getClients());
		_mutex->unlock();
		processMsg(vectMsg);

		_mutex->lock();
		_clientManager.checkDisconnectedClients(_roomManager);
		_socketServerTCP.sendAllData(_clientManager.getClients());
		_clientManager.checkDisconnectedClients(_roomManager);
		_mutex->unlock();
	}
	return (true);
}

void									Server::processUDPMessages(std::vector<UDPClientMsg> vectMsg)
{
	std::vector<UDPClientMsg>::iterator	it;

	it = vectMsg.begin();
	while (it != vectMsg.end())
	{
		std::cout << "[Process UDP Msg] cmdType :" << (*it).second->getCommandName() << std::endl;
		it++;
	}
}

bool									Server::UDPLoop()
{
	std::vector<UDPClientMsg>			vectMsg;
	std::vector<UDPClientMsg>::iterator	it;
	ServerClient						*client;
	int									tcpSocket;

	while (42)
	{
		vectMsg = _socketServerUDP.receiveData();
		it = vectMsg.begin();
		while (it != vectMsg.end())
		{
			if ((*it).first != NULL)
			{
				std::string str = (*it).second->getCommandArg();
				std::cout << "STR = " << str << std::endl;
				try
				{
					tcpSocket = std::stoi(str);
					std::cout << "TCP SOCKET = " << tcpSocket << std::endl;

					_mutex->lock();
					client = _clientManager.getClientByTCP(tcpSocket);
					if (client != NULL && client->getAddrUDP() == NULL)
						client->setAddrUDP((*it).first);
					_mutex->unlock();

				}
				catch (const std::exception &error)
				{
					std::cerr << "std::stoi error " << error.what() << std::endl;
				}
			}
			it++;
		}
		processUDPMessages(vectMsg);
		_mutex->lock();
		_socketServerUDP.sendAllData(_clientManager.getClients());
		_mutex->unlock();
	}
	return (true);
}
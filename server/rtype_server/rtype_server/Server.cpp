#include "Server.hh"

Server::Server() : _cmdManager(&_clientManager, &_roomManager)
{
	_acknowledgementNumber = 666;
	_pool = new ThreadPool();
	_mutex = new Mutex();
	_cmdManager.setMutex(_mutex);
}

Server::~Server()
{
}

bool	Server::init()
{
	if (_socketServerTCP.init("127.0.0.1", 42000) == false
		|| _socketServerTCP.launch() == false)
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

	case CREATE_ROOM:
		std::cout << "---------> CREATE ROOM" << std::endl;
		_cmdManager.cmdCreateRoom(client, cmd);
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
		//_cmdManager.cmdLaunchGame((*it).getClients(), (*it).getId());
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
	_pool->addThread(&threadTCP);
	_pool->addThread(&threadUDP);

	while (42)
	{
		processGames();
	}

	_pool->joinAll();
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
			_clientManager.addClient(clientSocketID);
		}

		_mutex->lock();
		vectMsg = _socketServerTCP.receiveData(_clientManager.getClients());
		_mutex->unlock();
		processMsg(vectMsg);

		_mutex->lock();
		_clientManager.checkDisconnectedClients(_roomManager);
		_mutex->unlock();
		//processGames();
		_mutex->lock();
		_socketServerTCP.sendAllData(_clientManager.getClients());
		_mutex->unlock();

		_mutex->lock();
		_clientManager.checkDisconnectedClients(_roomManager);
		_mutex->unlock();
	}
	return (true);
}

bool							Server::UDPLoop()
{
	int							len;
	sockaddr_in					receiverAddr;
	sockaddr_in					clientAddr;
	int							socketFd;
	char						buf[UDP_PACKET_SIZE];
	int							clientAddrSize;

	if ((socketFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		std::cout << "SOCKET UDP ERROR" << std::endl;
		return (false);
	}

	receiverAddr.sin_family = AF_INET;
	receiverAddr.sin_port = htons(9999);
	receiverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(socketFd, (SOCKADDR *)&receiverAddr, sizeof(receiverAddr)) == SOCKET_ERROR)
	{
		std::cout << "SOCKET BIND ERROR" << std::endl;
		return (false);
	}
	clientAddrSize = sizeof(clientAddr);
	std::cout << "UDP OK LAUNCH LOOP" << std::endl;
	while (42)
	{
		MemTools::set(buf, 0, UDP_PACKET_SIZE);
		len = recvfrom(socketFd, buf, UDP_PACKET_SIZE, 0, (struct sockaddr *)&clientAddr, &clientAddrSize);
		if (len > 1)
		{
			BasicCmd *cmd;

			cmd = static_cast<BasicCmd *>(Serialize::unserializeCommand(buf));
			std::cout << "Server: Total Bytes received: " <<  len << std::endl;
			std::cout << "Received [" << cmd->getArg(0) << "]" << std::endl;

		}
		else if (len <= 0)
			std::cout << "Server: Connection closed with error code: " << WSAGetLastError() << std::endl;
	}
	return (true);
}

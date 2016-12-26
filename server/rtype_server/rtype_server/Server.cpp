#include "Server.hh"


#define COLOR_GREEN		(10)
#define COLOR_CYAN		(11)
#define COLOR_RED		(12)
#define COLOR_MAGENTA	(13)
#define COLOR_YELLOW	(14)
#define COLOR_RESET		(15)

void  *gHConsole = GetStdHandle(STD_OUTPUT_HANDLE);

Server::Server() : _cmdManager(&_clientManager, &_roomManager)
{
	_acknowledgementNumber = 103;
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
		SetConsoleTextAttribute(gHConsole, COLOR_RED);
		std::cerr << "Initialization FAILED" << std::endl;
		SetConsoleTextAttribute(gHConsole, COLOR_RESET);
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
		SetConsoleTextAttribute(gHConsole, COLOR_CYAN);
		std::cout << "---------> HANDSHAKE SYN [" << client->getTCPSocket() << "]" << std::endl;
		SetConsoleTextAttribute(gHConsole, COLOR_RESET);
		_cmdManager.cmdHandshakeSyn(client, cmd, _acknowledgementNumber);
		break;

	case HANDSHAKE_ACK:
		SetConsoleTextAttribute(gHConsole, COLOR_CYAN);
		std::cout << "---------> HANDSHAKE ACK [" << client->getTCPSocket() << "]" << std::endl;
		SetConsoleTextAttribute(gHConsole, COLOR_RESET);
		_cmdManager.cmdHandshakeAck(client, cmd, _acknowledgementNumber);
		break;

	case GET_ROOM_LIST:
		SetConsoleTextAttribute(gHConsole, COLOR_CYAN);
		std::cout << "---------> GET ROOM LIST [" << client->getTCPSocket() << "]" << std::endl;
		SetConsoleTextAttribute(gHConsole, COLOR_RESET);
		_cmdManager.cmdListRoom(client, cmd);
		break;

	case JOIN_ROOM:
		SetConsoleTextAttribute(gHConsole, COLOR_CYAN);
		std::cout << "---------> JOIN ROOM [" << client->getTCPSocket() << "]" << std::endl;
		SetConsoleTextAttribute(gHConsole, COLOR_RESET);
		_cmdManager.cmdJoinRoom(client, cmd);
		break;

	case LEAVE_ROOM:
		SetConsoleTextAttribute(gHConsole, COLOR_CYAN);
		std::cout << "---------> LEAVE ROOM [" << client->getTCPSocket() << "]" << std::endl;
		SetConsoleTextAttribute(gHConsole, COLOR_RESET);
		_cmdManager.cmdLeaveRoom(client, cmd);
		break;

	case CREATE_ROOM:
		SetConsoleTextAttribute(gHConsole, COLOR_CYAN);
		std::cout << "---------> CREATE ROOM [" << client->getTCPSocket() << "]" << std::endl;
		SetConsoleTextAttribute(gHConsole, COLOR_RESET);		
		_cmdManager.cmdCreateRoom(client, cmd);

		break;

	case SET_STATUS:
		SetConsoleTextAttribute(gHConsole, COLOR_CYAN);
		std::cout << "---------> SET STATUS [" << client->getTCPSocket() << "]" << std::endl;
		_cmdManager.cmdSetStatus(client, cmd);
		SetConsoleTextAttribute(gHConsole, COLOR_RESET);
		break;

	case GET_ROOM:
		SetConsoleTextAttribute(gHConsole, COLOR_CYAN);
		std::cout << "---------> GET ROOM [" << client->getTCPSocket() << "]" << std::endl;
		SetConsoleTextAttribute(gHConsole, COLOR_RESET);
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
			processBasicCmd((*it).first, static_cast<BasicCmd *>((*it).second));
			break;
		default:
			std::cout << "NO CMD" << std::endl;
			break;
		}
		std::cout << "End Processing" << std::endl;
		it++;
	}
}

void							Server::checkRoomsReadyToLaunch()
{
	std::vector<Room>			roomsReadyToLaunch;
	std::vector<Room>::iterator	it;

	_mutex->lock();
	roomsReadyToLaunch = _roomManager.getRoomsReadyToLaunch();
	_mutex->unlock();
	it = roomsReadyToLaunch.begin();
	while (it != roomsReadyToLaunch.end())
	{
		SetConsoleTextAttribute(gHConsole, COLOR_GREEN);
		std::cout << "Room [" << (*it).getName() << "] is READY" << std::endl;
		SetConsoleTextAttribute(gHConsole, COLOR_RESET);
		_cmdManager.cmdLaunchGame((*it).getClients(), (*it).getId());
		it++;
	}
}

void							Server::processGames()
{
	std::vector<Room>			roomsReadyToPlay;
	std::vector<Room>::iterator	it;

	checkRoomsReadyToLaunch();

	_mutex->lock();
	roomsReadyToPlay = _roomManager.getRoomsReadyToPlay();
	_mutex->unlock();
	
	it = roomsReadyToPlay.begin();
	while (it != roomsReadyToPlay.end())
	{
		_gameManager.updateGame(*it);
		it++;
	}
}

bool							Server::launch()
{
	Thread						threadTCP;
	Thread						threadUDP;

	threadTCP.createThread(std::bind(&Server::TCPLoop, this));
	threadUDP.createThread(std::bind(&Server::UDPLoop, this));
	_pool.addThread(&threadTCP);
	_pool.addThread(&threadUDP);

	while (42)
	{
		Sleep(10);
		processGames();
	}

	_pool.joinAll();
	return (true);
}

bool							Server::TCPLoop()
{
	std::vector<int>			socketsClients;
	NewClientInfo				newClientInfo;
	std::vector<ClientMsg>		vectMsg;
	
	while (42)
	{
		_mutex->lock();
		_socketServerTCP.selectFds(_clientManager.getClientsTCPSockets());
		_mutex->unlock();

		if ((newClientInfo = _socketServerTCP.acceptNewClient()).first != -1)
		{
			_mutex->lock();
			_clientManager.addClient(newClientInfo.first, newClientInfo.second);
			_mutex->unlock();
		}
		else
			delete(newClientInfo.second);

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

void											Server::processUDPMessages(const std::vector<ICommand *> &vectMsg)
{
	std::vector<ICommand *>::const_iterator	it;
	InputCmd								*input;
	int										id;
	ServerClient							*client;

	it = vectMsg.begin();
	while (it != vectMsg.end())
	{
		if (*it != NULL)
		{
			std::cout << "[Process UDP Msg] cmdType :" << (*it)->getCommandName() << std::endl;
		/*	input = static_cast<InputCmd *>(*it);
			id = input->getId();
			if ((client = _clientManager.getClientByTCP(id)) != NULL)
			{
				_gameManager.move(client, input->getKey());
			}*/
		}
			
		it++;
	}

}

bool									Server::UDPLoop()
{
	std::vector<ICommand *>			vectMsg;

	while (42)
	{
		_socketServerUDP.selectFds();
		vectMsg = _socketServerUDP.receiveData();
		processUDPMessages(vectMsg);
		_mutex->lock();
		_socketServerUDP.sendAllData(_clientManager.getClients());
		_mutex->unlock();
	}
	return (true);
}
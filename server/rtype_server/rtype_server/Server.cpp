#include "Server.hh"

#define COLOR_GREEN		(10)
#define COLOR_CYAN		(11)
#define COLOR_RED		(12)
#define COLOR_MAGENTA		(13)
#define COLOR_YELLOW		(14)
#define COLOR_RESET		(15)

#define COLOR_GREEN_L		"\033[34m"
#define COLOR_CYAN_L		"\033[36m"
#define COLOR_RED_L		"\033[31m"
#define COLOR_MAGENTA_L		"\033[35m"
#define COLOR_YELLOW_L		"\033[33m"
#define COLOR_RESET_L		"\033[0m"

#ifdef _WIN32
void  *gHConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

Server::Server() : _cmdManager(&_clientManager, &_roomManager)
{
	_acknowledgementNumber = 103;
	_mutex = new Mutex();
	_cmdManager.setMutex(_mutex);
	std::srand(std::time(NULL));
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
#ifdef _WIN32
	  SetConsoleTextAttribute(gHConsole, COLOR_RED);
	  std::cerr << "Initialization FAILED" << std::endl;
	  SetConsoleTextAttribute(gHConsole, COLOR_RESET);
#elif __linux__
	  std::cerr  << COLOR_RED_L << "Initialization FAILED" << COLOR_RESET_L <<  std::endl;
#endif
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
#ifdef _WIN32
	  SetConsoleTextAttribute(gHConsole, COLOR_CYAN);
	  std::cout << "---------> HANDSHAKE SYN [" << client->getTCPSocket() << "]" << std::endl;
	  SetConsoleTextAttribute(gHConsole, COLOR_RESET);
#elif __linux__
	  std::cout << COLOR_CYAN_L << "---------> HANDSHAKE SYN [" << client->getTCPSocket() << "]" << COLOR_RESET_L << std::endl;
#endif
	  _cmdManager.cmdHandshakeSyn(client, cmd, _acknowledgementNumber);
	  break;
	case HANDSHAKE_ACK:
#ifdef _WIN32
	  SetConsoleTextAttribute(gHConsole, COLOR_CYAN);
	  std::cout << "---------> HANDSHAKE ACK [" << client->getTCPSocket() << "]" << std::endl;
	  SetConsoleTextAttribute(gHConsole, COLOR_RESET);
#elif __linux__
	  std::cout << COLOR_CYAN_L << "---------> HANDSHAKE ACK [" << client->getTCPSocket() << "]" << COLOR_RESET_L << std::endl;
#endif
	  _cmdManager.cmdHandshakeAck(client, cmd, _acknowledgementNumber);
	  break;

	case GET_ROOM_LIST:
#ifdef _WIN32
	  SetConsoleTextAttribute(gHConsole, COLOR_CYAN);
	  std::cout << "---------> GET ROOM LIST [" << client->getTCPSocket() << "]" << std::endl;
	  SetConsoleTextAttribute(gHConsole, COLOR_RESET);
	  #elif __linux__
	  std::cout << COLOR_CYAN_L << "---------> GET ROOM LIST [" << client->getTCPSocket() << "]" << COLOR_RESET_L << std::endl;
#endif
	  _cmdManager.cmdListRoom(client, cmd);
	  break;

	case JOIN_ROOM:
#ifdef _WIN32
	  SetConsoleTextAttribute(gHConsole, COLOR_CYAN);
	  std::cout << "---------> JOIN ROOM [" << client->getTCPSocket() << "]" << std::endl;
	  SetConsoleTextAttribute(gHConsole, COLOR_RESET);
#elif __linux__
	  std::cout << COLOR_CYAN_L << "---------> JOIN ROOM [" << client->getTCPSocket() << "]" << COLOR_RESET_L << std::endl;
#endif
	  _cmdManager.cmdJoinRoom(client, cmd);
	  break;

	case LEAVE_ROOM:
	  #ifdef _WIN32
	  SetConsoleTextAttribute(gHConsole, COLOR_CYAN);
	  std::cout << "---------> LEAVE ROOM [" << client->getTCPSocket() << "]" << std::endl;
	  SetConsoleTextAttribute(gHConsole, COLOR_RESET);
#elif __linux__
	  std::cout << COLOR_CYAN_L << "---------> LEAVE ROOM [" << client->getTCPSocket() << "]" << COLOR_RESET_L << std::endl;
#endif
	  _cmdManager.cmdLeaveRoom(client, cmd);
	  break;

	case CREATE_ROOM:
	  #ifdef _WIN32
	  SetConsoleTextAttribute(gHConsole, COLOR_CYAN);
	  std::cout << "---------> CREATE ROOM [" << client->getTCPSocket() << "]" << std::endl;
	  SetConsoleTextAttribute(gHConsole, COLOR_RESET);
	  #elif __linux__
	  std::cout << COLOR_CYAN_L << "---------> CREATE ROOM [" << client->getTCPSocket() << "]" << COLOR_RESET_L << std::endl;
	  #endif
	  _cmdManager.cmdCreateRoom(client, cmd);
	  break;

	case SET_STATUS:
	  #ifdef _WIN32
	  SetConsoleTextAttribute(gHConsole, COLOR_CYAN);
	  std::cout << "---------> SET STATUS [" << client->getTCPSocket() << "]" << std::endl;
	  _cmdManager.cmdSetStatus(client, cmd);
	  SetConsoleTextAttribute(gHConsole, COLOR_RESET);
#elif __linux__
	  std::cout << COLOR_CYAN_L<< "---------> SET STATUS [" << client->getTCPSocket() << "]" << COLOR_RESET_L << std::endl;
	  #endif
	  break;

	case GET_ROOM:
	  #ifdef _WIN32
	  SetConsoleTextAttribute(gHConsole, COLOR_CYAN);
	  std::cout << "---------> GET ROOM [" << client->getTCPSocket() << "]" << std::endl;
	  SetConsoleTextAttribute(gHConsole, COLOR_RESET);
	  #elif __linux__
	  std::cout << COLOR_CYAN_L << "---------> GET ROOM [" << client->getTCPSocket() << "]" << COLOR_RESET_L << std::endl;
#endif
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
	  #ifdef _WIN32
		SetConsoleTextAttribute(gHConsole, COLOR_GREEN);
		std::cout << "Room [" << (*it).getName() << "] is READY" << std::endl;
		SetConsoleTextAttribute(gHConsole, COLOR_RESET);
#elif __linux__
		std::cout << COLOR_GREEN_L << "Room [" << (*it).getName() << "] is READY" << COLOR_RESET_L << std::endl;
#endif
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
		_mutex->lock();
		(*it).updateGame();
		_mutex->unlock();
		it++;
	}
}

# define GAME_LOOP_TIME (100)

bool							Server::launch()
{
	Thread						threadTCP;
	Thread						threadUDP;

	threadTCP.createThread(std::bind(&Server::TCPLoop, this));
	threadUDP.createThread(std::bind(&Server::UDPLoop, this));
	_pool.addThread(&threadTCP);
	_pool.addThread(&threadUDP);

	std::chrono::high_resolution_clock::time_point		t1;
	std::chrono::high_resolution_clock::time_point		t2;
	double												duration;

	t1 = std::chrono::high_resolution_clock::now();

	while (42)
	{
		t2 = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
		if (duration >= GAME_LOOP_TIME)
		{
			processGames();
			t1 = std::chrono::high_resolution_clock::now();
		}
		else
			Sleep(GAME_LOOP_TIME - duration);
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
			_clientManager.addClient(newClientInfo.first, newClientInfo.second, _roomManager);
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
			//std::cout << "[Process UDP Msg] cmdType :" << (*it)->getCommandName() << std::endl;

			input = static_cast<InputCmd *>(*it);
			id = input->getId();
			_mutex->lock();
			if ((client = _clientManager.getClientByTCP(id)) != NULL)
			{
				client->addInput(*input);
			}
			_mutex->unlock();
		}
		it++;
	}

}

bool									Server::UDPLoop()
{
	std::vector<ICommand *>			vectMsg;
	int nbMsg;

	while (42)
	{
		nbMsg = 0;
		if (_socketServerUDP.selectFds() != -1)
		//while (_socketServerUDP.selectFds() != -1)
		{
			//std::cout << "Msg nb" << nbMsg << std::endl;
			vectMsg = _socketServerUDP.receiveData();
			processUDPMessages(vectMsg);
			//nbMsg++;
		}
		_mutex->lock();
		_socketServerUDP.sendAllData(_clientManager.getClients());
		_mutex->unlock();
	}
	return (true);
}

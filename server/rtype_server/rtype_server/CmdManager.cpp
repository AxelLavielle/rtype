#include "CmdManager.hh"

CmdManager::CmdManager(ClientManager *cM, RoomManager *rM)
{
	_clientManager = cM;
	_roomManager = rM;
}

CmdManager::~CmdManager()
{
}

void	CmdManager::setMutex(AMutex *mutex)
{
	_mutex = mutex;
}

void	CmdManager::closeSocket(int socket)
{
#ifdef  _WIN32
	closesocket(socket);
#elif	__linux__
	close(socket);
#endif
}

void				CmdManager::cmdHandshakeSyn(ServerClient *client, BasicCmd *msgClient,
												const int acknowledgementNumber)
{
	BasicCmd		cmd;
	std::string		handshake;
	Serialize		serializer;
	char			*msgSerialized;

	handshake = msgClient->getArg(0);
	std::cout << "[HandshakeSyn] : " << handshake << std::endl;
	cmd.setCommandType(HANDSHAKE_SYN_ACK);
	cmd.addArg(std::to_string(acknowledgementNumber));
	cmd.addArg(std::to_string(std::stoi(handshake) + 1));
	msgSerialized = serializer.serialize(&cmd);
	std::cout << "[HandshakeSyn] Sending : " << cmd.getCommandArg() << std::endl;
	_clientManager->addDataToSendTCP(client->getTCPSocket(), msgSerialized, sizeof(cmd));
}

void			CmdManager::cmdHandshakeAck(ServerClient *client, BasicCmd *msgClient,
											const int acknowledgementNumber)
{
	std::string	handshake;

	std::cout << "[Handshake Ack] : init" << std::endl;
	handshake = msgClient->getArg(0);
	std::cout << "[Handshake Ack] : " << handshake << std::endl;
	if (std::stoi(handshake) == acknowledgementNumber + 1)
	{
		std::cout << std::endl << "Client [" << client->getTCPSocket() << "] is now CONNECTED" << std::endl << std::endl;
		client->setLogged(true);

		_mutex->lock();
		client->setStatus(true);
		_roomManager->addClientToRoom(client, "blih");
		_mutex->unlock();
	}
	else
	{
		closeSocket(client->getTCPSocket());
		_clientManager->removeClient(client);
	}
}

void								CmdManager::cmdCreateRoom(ServerClient *client, BasicCmd *msgClient)
{
	int								newRoom;
	std::string						roomName;
	std::string						playerName;
	BasicCmd						reply;
	char							*msgSerialized;
	Serialize						serializer;

	roomName = msgClient->getArg(0);
	playerName = msgClient->getArg(1);
	client->setPlayerName(playerName);

	_mutex->lock();
	newRoom = _roomManager->addRoom(roomName);
	_mutex->unlock();
	std::cout << "Player " << playerName << " created |" << roomName
			  << "| ---> Id = " << std::to_string(newRoom) << std::endl;
	reply.setCommandType(REPLY_CODE);
	if (client->getCurrentRoom() != -1) // ALREADY IN ROOM
	{
		reply.setCommandArg(std::to_string(NOT_IN_LOBBY));
	}
	else
	{
		reply.setCommandArg(std::to_string(ROOM_CREATED));
		_mutex->lock();
		_roomManager->addClientToRoom(client, newRoom);
		_mutex->unlock();
	}
	msgSerialized = serializer.serialize(&reply);
	_clientManager->addDataToSendTCP(client->getTCPSocket(), msgSerialized, sizeof(reply));
}

void							CmdManager::cmdListRoom(ServerClient *client, BasicCmd *msgClient)
{
	ListRoomCmd					roomListMsg;
	Serialize					serializer;
	std::vector<Room>			roomList;
	std::vector<Room>::iterator	it;
	char						*msgSerialized;


	(void)msgClient;
	_mutex->lock();
	roomList = _roomManager->getRoomList();
	_mutex->unlock();

	it = roomList.begin();
	while (it != roomList.end())
	{
		roomListMsg.addRoom((*it).getId(), (*it).getName(), (*it).getNbClients());
		it++;
	}
	std::cout << std::endl << std::endl;
	roomListMsg.getCommandArg();
	msgSerialized = serializer.serialize(&roomListMsg);

	_clientManager->addDataToSendTCP(client->getTCPSocket(), msgSerialized, sizeof(roomListMsg));
}

void			CmdManager::cmdJoinRoom(ServerClient *client, BasicCmd *msgClient)
{
	int			idRoom;
	std::string playerName;
	BasicCmd	reply;
	char		*msgSerialized;
	Serialize	serializer;

	idRoom = std::stoi(msgClient->getArg(0));
	playerName = msgClient->getArg(1);
	reply.setCommandType(REPLY_CODE);
	std::cout << "Player [" << playerName << "] wants to join room [" << idRoom << "]";

	if (client->getCurrentRoom() != -1)
	{
		std::cout << "Not in LOBBY !" << std::endl;
		reply.setCommandArg(std::to_string(NOT_IN_LOBBY));
	}
	else
	{
		try
		{
			_mutex->lock();
			_roomManager->getRoomById(idRoom);
			client->setStatus(true);
			if (_roomManager->addClientToRoom(client, _roomManager->getRoomById(idRoom).getId()) == true)
			{
				std::cout << "Room JOINED !" << std::endl;
				reply.setCommandArg(std::to_string(ROOM_JOINED));
			}
			else
			{
				std::cout << "Room FULL !" << std::endl;
				reply.setCommandArg(std::to_string(ROOM_FULL));
			}

			_mutex->unlock();
		}
		catch (const std::exception &error)
		{
			std::cerr << "############ " << error.what() << std::endl;
			reply.setCommandArg(std::to_string(ROOM_NOT_EXIST));
		}
	}

	msgSerialized = serializer.serialize(&reply);
	_clientManager->addDataToSendTCP(client->getTCPSocket(), msgSerialized, sizeof(reply));
}

void			CmdManager::cmdLeaveRoom(ServerClient *client, BasicCmd *msgClient)
{
	BasicCmd	reply;
	char		*msgSerialized;

	reply.setCommandType(REPLY_CODE);
	if (client->getCurrentRoom() != -1)
	{
		std::cout << "Leaving Room " << client->getCurrentRoom() << std::endl;
		_roomManager->removeClientFromRoom(client, client->getCurrentRoom());
		client->setCurrentRoom(-1);
		reply.setCommandArg(std::to_string(LEFT_ROOM));
	}
	else
		reply.setCommandArg(std::to_string(NOT_IN_ROOM));

	msgSerialized = Serialize::serialize(&reply);
	_clientManager->addDataToSendTCP(client->getTCPSocket(), msgSerialized, sizeof(reply));
}

void			CmdManager::cmdSetStatus(ServerClient *client, BasicCmd *msgClient)
{
	BasicCmd	reply;
	char		*msgSerialized;

	reply.setCommandType(REPLY_CODE);
	if (client->getCurrentRoom() == -1)
		reply.setCommandArg(std::to_string(NOT_IN_ROOM));
	else
	{
		if (client->isReady())
			client->setStatus(false);
		else
			client->setStatus(true);
		reply.setCommandArg(std::to_string(STATUS_CHANGED));
	}
	msgSerialized = Serialize::serialize(&reply);
	_clientManager->addDataToSendTCP(client->getTCPSocket(), msgSerialized, sizeof(reply));
}

void											CmdManager::cmdLaunchGame(const std::vector<ServerClient *> &clients, const int idRoom)
{
	BasicCmd									cmd;
	char										*msgSerialized;
	Serialize									serializer;
	std::vector<ServerClient *>::const_iterator	it;

	std::cout << std::endl << "LAUNCH GAME IN ROOM [" << idRoom << "]" << std::endl;
	it = clients.begin();
	cmd.setCommandType(LAUNCH_GAME);
	cmd.addArg(std::to_string(idRoom));
	while (it != clients.end())
	{
		cmd.addArg(std::to_string((*it)->getTCPSocket()));
		msgSerialized = serializer.serialize(&cmd);
		_mutex->lock();
		_clientManager->addDataToSendTCP((*it)->getTCPSocket(), msgSerialized, sizeof(cmd));
		_mutex->unlock();
		it++;
	}
	_mutex->lock();
	_roomManager->getRoomById(idRoom).setInGame(true);
	_mutex->unlock();
	//launchUDP();
}

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
	BasicCmd		*test;
	std::string		handshake;
	char			*msgSerialized;

	test = NULL;
	handshake = msgClient->getArg(0);
	std::cout << "[HandshakeSyn] : " << handshake << std::endl;
	cmd.setCommandType(HANDSHAKE_SYN_ACK);
	cmd.addArg(std::to_string(acknowledgementNumber));
	try
	{
		cmd.addArg(std::to_string(std::stoi(handshake) + 1));
	}
	catch (const std::exception &error)
	{
		return;
	}
	msgSerialized = Serialize::serialize(&cmd);
	std::cout << "[HandshakeSyn] Sending : " << cmd.getCommandArg() << std::endl;

	test = static_cast<BasicCmd *>(Serialize::unserializeCommand(msgSerialized));
	//std::cout << "______________________ TEST ARG = " << test->getArg(0) << std::endl;
	_mutex->lock();
	_clientManager->addDataToSendTCP(client->getTCPSocket(), msgSerialized, sizeof(cmd));
	_mutex->unlock();
	std::cout << std::endl;
}

void			CmdManager::cmdHandshakeAck(ServerClient *client, BasicCmd *msgClient,
											const int acknowledgementNumber)
{
	std::string	handshake;

	handshake = msgClient->getArg(0);
	std::cout << "[Handshake Ack] : " << handshake << std::endl;
	if (std::stoi(handshake) == acknowledgementNumber + 1)
	{
		std::cout << std::endl << "Client [" << client->getTCPSocket() << "] is now CONNECTED" << std::endl << std::endl;
		client->setLogged(true);
	}
	else
	{
		std::cout << std::endl << "Client [" << client->getTCPSocket() << "] is DELETED" << std::endl << std::endl;
		closeSocket(client->getTCPSocket());
		_mutex->lock();
		_clientManager->removeClient(client);
		_mutex->unlock();
	}
	std::cout << std::endl;
}

void								CmdManager::cmdCreateRoom(ServerClient *client, BasicCmd *msgClient)
{
	int								newRoom;
	std::string						roomName;
	std::string						playerName;
	BasicCmd						reply;
	char							*msgSerialized;
	Serialize						serializer;

	if (client->isLogged() == false)
		return;
	roomName = msgClient->getArg(0);
	playerName = msgClient->getArg(1);

	_mutex->lock();
	newRoom = _roomManager->addRoom(roomName);
	_mutex->unlock();
	reply.setCommandType(REPLY_CODE);
	if (client->getCurrentRoom() != -1) // ALREADY IN ROOM
	{
		reply.setCommandArg(std::to_string(NOT_IN_LOBBY));
	}
	else
	{
		client->setPlayerName(playerName);
		std::cout << "Player " << playerName << " created |" << roomName
			<< "| ---> Id = " << std::to_string(newRoom) << std::endl;
		reply.setCommandArg(std::to_string(ROOM_CREATED));
		_mutex->lock();
		_roomManager->addClientToRoom(client, newRoom);
		_mutex->unlock();
	}
	msgSerialized = serializer.serialize(&reply);
	_mutex->lock();
	_clientManager->addDataToSendTCP(client->getTCPSocket(), msgSerialized, sizeof(reply));
	sendUpdateRoom(client);
	_mutex->unlock();
	std::cout << std::endl;
}

void							CmdManager::removeEmptyRooms()
{
	std::vector<Room>			roomList;
	std::vector<Room>::iterator	it;

	_mutex->lock();
	roomList = _roomManager->getRoomList();
	_mutex->unlock();
	it = roomList.begin();
	while (it != roomList.end())
	{
		if ((*it).getNbClients() == 0)
		{
			_mutex->lock();
			_roomManager->removeRoom((*it).getId());
			_mutex->unlock();
		}
		it++;
	}
}

void							CmdManager::cmdListRoom(ServerClient *client, BasicCmd *msgClient)
{
	ListRoomCmd					roomListMsg;
	std::vector<Room>			roomList;
	std::vector<Room>::iterator	it;
	char						*msgSerialized;

	if (client->isLogged() == false)
		return;

	removeEmptyRooms();

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
	msgSerialized = Serialize::serialize(&roomListMsg);
	_mutex->lock();
	_clientManager->addDataToSendTCP(client->getTCPSocket(), msgSerialized, sizeof(roomListMsg));
	_mutex->unlock();
	std::cout << std::endl;
}

void							CmdManager::cmdRoomInfo(ServerClient *client, BasicCmd *msgClient)
{
	Room						*room;
	RoomInfoCmd					roomInfoMsg;
	char						*msgSerialized;
	BasicCmd					reply;
	std::vector<ServerClient *>::const_iterator it;

	if (client->isLogged() == false)
		return;
	(void)msgClient;
	if (client->getCurrentRoom() == -1)
	{
		reply.setCommandType(REPLY_CODE);
		reply.setCommandArg(std::to_string(NOT_IN_ROOM));
		msgSerialized = Serialize::serialize(&reply);
		_mutex->lock();
		_clientManager->addDataToSendTCP(client->getTCPSocket(), msgSerialized, sizeof(reply));
		_mutex->unlock();
		return;
	}
	room = NULL;
	_mutex->lock();
	room = _roomManager->getRoomById(client->getCurrentRoom());
	_mutex->unlock();

	std::cout << "NAME = " << room->getName() << std::endl;
	roomInfoMsg.setName(room->getName());
	std::vector<ServerClient *> vect;
	if (room->getClients().size() > 0)
	{
		vect = room->getClients();
		it = vect.begin();
		while (it != vect.end())
		{
			std::cout << "Adding player (" << (*it)->getPlayerName() << ")" << std::endl;
			roomInfoMsg.addPlayer((*it)->getPlayerName(), (*it)->isReady());
			it++;
		}
	}

	msgSerialized = Serialize::serialize(&roomInfoMsg);
	_mutex->lock();
	_clientManager->addDataToSendTCP(client->getTCPSocket(), msgSerialized, sizeof(roomInfoMsg));
	_mutex->unlock();
	std::cout << std::endl;
}

void			CmdManager::cmdJoinRoom(ServerClient *client, BasicCmd *msgClient)
{
	int			idRoom;
	std::string playerName;
	BasicCmd	reply;
	char		*msgSerialized;
	Serialize	serializer;
	Room		*room;

	if (client->isLogged() == false)
		return;
	(void)msgClient;
	idRoom = std::stoi(msgClient->getArg(0));
	playerName = msgClient->getArg(1);
	reply.setCommandType(REPLY_CODE);
	std::cout << "Player [" << playerName << "] wants to join room [" << idRoom << "]" << std::endl;

	if (client->getCurrentRoom() != -1)
	{
		std::cout << "Not in LOBBY !" << std::endl;
		reply.setCommandArg(std::to_string(NOT_IN_LOBBY));
	}
	else
	{
		_mutex->lock();
		try
		{
			room = _roomManager->getRoomById(idRoom);
			
			if (room->isReady() == true)
			{
				std::cout << "Room ALREADY IN GAME !" << std::endl;
				reply.setCommandArg(std::to_string(ROOM_FULL));
			}
			else if (_roomManager->addClientToRoom(client, idRoom) == true)
			{
				client->setPlayerName(playerName);
				std::cout << "Room JOINED !" << std::endl;
				reply.setCommandArg(std::to_string(ROOM_JOINED));
			}
			else
			{
				std::cout << "Room FULL !" << std::endl;
				reply.setCommandArg(std::to_string(ROOM_FULL));
			}

		}
		catch (const std::exception &error)
		{
			std::cerr << "############ " << error.what() << std::endl;
			reply.setCommandArg(std::to_string(ROOM_NOT_EXIST));
		}
		_mutex->unlock();
	}

	msgSerialized = serializer.serialize(&reply);
	_mutex->lock();
	_clientManager->addDataToSendTCP(client->getTCPSocket(), msgSerialized, sizeof(reply));
	sendUpdateRoom(client);
	_mutex->unlock();
	std::cout << std::endl;
}

void			CmdManager::cmdLeaveRoom(ServerClient *client, BasicCmd *msgClient)
{
	BasicCmd	reply;
	char		*msgSerialized;

	if (client->isLogged() == false)
		return;
	(void)msgClient;
	reply.setCommandType(REPLY_CODE);
	if (client->getCurrentRoom() != -1)
	{
		std::cout << "[" << client->getPlayerName() << "] Leaving Room " << client->getCurrentRoom() << std::endl;
		_mutex->lock();
		_roomManager->removeClientFromRoom(client, client->getCurrentRoom());
		_mutex->unlock();
		client->setCurrentRoom(-1);
		reply.setCommandArg(std::to_string(LEFT_ROOM));
		_mutex->lock();
		sendUpdateRoom(client);
		_mutex->unlock();
	}
	else
		reply.setCommandArg(std::to_string(NOT_IN_ROOM));

	msgSerialized = Serialize::serialize(&reply);
	_mutex->lock();
	_clientManager->addDataToSendTCP(client->getTCPSocket(), msgSerialized, sizeof(reply));
	_mutex->unlock();
	std::cout << std::endl;
}

void			CmdManager::cmdSetStatus(ServerClient *client, BasicCmd *msgClient)
{
	BasicCmd	reply;
	char		*msgSerialized;

	std::cout << "HELLO CMD SET STATUS !" << std::endl;
	if (client->isLogged() == false)
		return;
	(void)msgClient;
	reply.setCommandType(REPLY_CODE);
	if (client->getCurrentRoom() == -1)
	  {
		reply.setCommandArg(std::to_string(NOT_IN_ROOM));
		std::cout << "NOT IN ROOM !" << std::endl;
	  }
	else
	{
		if (client->isReady())
			client->setStatus(false);
		else
			client->setStatus(true);
		reply.setCommandArg(std::to_string(STATUS_CHANGED));
		std::cout << "Status changed !" << std::endl;
		_mutex->lock();
		sendUpdateRoom(client);
		_mutex->unlock();
		std::cout << "Sent Update Room !" << std::endl;
	}
	msgSerialized = Serialize::serialize(&reply);
	_mutex->lock();
	_clientManager->addDataToSendTCP(client->getTCPSocket(), msgSerialized, sizeof(reply));
	_mutex->unlock();
	std::cout << std::endl;
}

void											CmdManager::cmdLaunchGame(const std::vector<ServerClient *> &clients, const int idRoom)
{
	char										*msgSerialized;
	std::vector<ServerClient *>::const_iterator	it;

	std::cout << std::endl << "LAUNCH GAME IN ROOM [" << idRoom << "]" << std::endl;
	it = clients.begin();
	while (it != clients.end())
	{
		BasicCmd									cmd;

		cmd.setCommandType(LAUNCH_GAME);
		cmd.addArg(std::to_string(idRoom));

		std::cout << "Sending LAUNCH GAME to " << (*it)->getTCPSocket() << std::endl;
		cmd.addArg(std::to_string((*it)->getTCPSocket()));
		std::cout << "Sending -------> " << cmd.getCommandArg() << std::endl;
		msgSerialized = Serialize::serialize(&cmd);
		_mutex->lock();
		_clientManager->addDataToSendTCP((*it)->getTCPSocket(), msgSerialized, sizeof(cmd));
		_mutex->unlock();
		it++;
	}
	_mutex->lock();
	_roomManager->getRoomById(idRoom)->setReady(true);
	_roomManager->getRoomById(idRoom)->initGame();
	_mutex->unlock();
	std::cout << std::endl;
}

void										CmdManager::sendUpdateRoom(ServerClient *client)
{
	std::vector<ServerClient *>				vectClients;
	std::vector<ServerClient *>::iterator	it;
	BasicCmd								infoCmd;
	char									*msgSerialized;

	if (client->getCurrentRoom() == -1)
		return;
	infoCmd.setCommandType(UPDATE_ROOM);
	msgSerialized = Serialize::serialize(&infoCmd);
	vectClients = _roomManager->getRoomById(client->getCurrentRoom())->getClients();
	
	it = vectClients.begin();
	while (it != vectClients.end())
	{
		//if ((*it)->getTCPSocket() != client->getTCPSocket())
		//{
		std::cout << "Sending UPDATE ROOM to [" << (*it)->getTCPSocket() << "]" << std::endl;
		_clientManager->addDataToSendTCP((*it)->getTCPSocket(), msgSerialized, sizeof(infoCmd));
		//}
		it++;
	}
}

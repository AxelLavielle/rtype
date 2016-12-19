#include "CmdManager.hh"

CmdManager::CmdManager(ClientManager *cM, RoomManager *rM)
{
	_clientManager = cM;
	_roomManager = rM;
}

CmdManager::~CmdManager()
{
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
	_clientManager->addDataToSend(client->getTCPSocket(), msgSerialized, sizeof(cmd));
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
	newRoom = _roomManager->addRoom(roomName);
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
		_roomManager->addClientToRoom(client, newRoom);
	}
	msgSerialized = serializer.serialize(&reply);
	_clientManager->addDataToSend(client->getTCPSocket(), msgSerialized, sizeof(reply));
}

void							CmdManager::cmdListRoom(ServerClient *client, BasicCmd *msgClient)
{
	ListRoomCmd					roomListMsg;
	Serialize					serializer;
	std::vector<Room>			roomList;
	std::vector<Room>::iterator	it;
	char						*msgSerialized;


	(void)msgClient;
	_roomManager->addRoom("test1");
	_roomManager->addRoom("blih");
	_roomManager->addRoom("azertyu");

	client->setStatus(true);
	_roomManager->addClientToRoom(client, "blih");

	roomList = _roomManager->getRoomList();
	it = roomList.begin();
	while (it != roomList.end())
	{
		roomListMsg.addRoom((*it).getId(), (*it).getName(), (*it).getNbClients());
		it++;
	}
	std::cout << std::endl << std::endl;
	roomListMsg.getCommandArg();
	msgSerialized = serializer.serialize(&roomListMsg);

	_clientManager->addDataToSend(client->getTCPSocket(), msgSerialized, sizeof(roomListMsg));
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
	try
	{
		_roomManager->getRoomById(idRoom);
		
		if (_roomManager->addClientToRoom(client, _roomManager->getRoomById(idRoom).getId()) == true)
			reply.setCommandArg(std::to_string(ROOM_JOINED));
		else
			reply.setCommandArg(std::to_string(ROOM_FULL));
	}
	catch (const std::exception &error)
	{
		std::cerr << "############ " << error.what() << std::endl;
		reply.setCommandArg(std::to_string(ROOM_NOT_EXIST));
	}
	msgSerialized = serializer.serialize(&reply);
	_clientManager->addDataToSend(client->getTCPSocket(), msgSerialized, sizeof(reply));
}

void			CmdManager::cmdLaunchGame(const std::vector<ServerClient *> &clients, const int idRoom)
{
	BasicCmd									cmd;
	char										*msgSerialized;
	Serialize									serializer;
	std::vector<ServerClient *>::const_iterator	it;

	it = clients.begin();
	cmd.setCommandType(LAUNCH_GAME);
	cmd.addArg(std::to_string(idRoom));
	while (it != clients.end())
	{
		cmd.addArg(std::to_string((*it)->getPlayerId()));
		msgSerialized = serializer.serialize(&cmd);
		_clientManager->addDataToSend((*it)->getTCPSocket(), msgSerialized, sizeof(cmd));
	}

}
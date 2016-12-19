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

//void								CmdManager::cmdCreateRoom(ServerClient *client, const std::string &msgClient)
//{
//	std::string						msg;
//	int								newRoom;
//	std::string						roomName;
//
//	roomName = msgClient.substr(5);
//	roomName.pop_back();
//	newRoom = _roomManager->addRoom(roomName);
//	msg = "Created |" + roomName + "| ---> Id = " + std::to_string(newRoom) + "\n";
//
//	_clientManager->addDataToSend(client->getTCPSocket(), msg.c_str(), msg.size());
//	_roomManager->addClientToRoom(client, newRoom);
//}

void				CmdManager::cmdHandshakeSyn(ServerClient *client, BasicCmd *msgClient,
															int acknowledgementNumber)
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
											int acknowledgementNumber)
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

	_roomManager->addClientToRoom(client, "blih");

	roomList = _roomManager->getRoomList();
	it = roomList.begin();
	while (it != roomList.end())
	{
		std::cout << "Adding Room (" << (*it).getName() << ", " << (*it).getNbClients() << ")" << std::endl;
		roomListMsg.addRoom((*it).getName(), (*it).getNbClients());
		it++;
	}
	std::cout << std::endl << std::endl;
	msgSerialized = serializer.serialize(&roomListMsg);

	/*std::vector<std::pair<std::string, int>>			roomInfos;
	std::vector<std::pair<std::string, int>>::iterator	itTest;

	roomInfos = roomListMsg.getAllRooms();
*/
	/*itTest = roomInfos.begin();
	while (itTest != roomInfos.end())
	{
		std::cout << "Room serialized : (" << (*itTest).first << ", " << (*itTest).second << ")" << std::endl;
		itTest++;
	}
	*/
	//std::cout << std::endl << std::endl;
	//msg = "RoomList :\n" + _roomManager->getRoomListString() + "\n";
	_clientManager->addDataToSend(client->getTCPSocket(), msgSerialized, sizeof(roomListMsg));
}

//void			CmdManager::cmdJoinRoom(ServerClient *client, const std::string &msgClient)
//{
//	std::string roomName;
//	std::string msg;
//	
//	roomName = msgClient.substr(5);
//	roomName.pop_back();
//	msg = "I want to join |" + roomName + "|\n";
//
//	try
//	{
//		_roomManager->getRoomByName(roomName);
//		msg += "Room exist :D : " + _roomManager->getRoomByName(roomName).getName() + "\n";
//		if (_roomManager->addClientToRoom(client, _roomManager->getRoomByName(roomName).getId()) == true)
//			msg += "Yes I joined room!\n";
//		else
//			msg += "Nope, room is full...\n";
//	}
//	catch (const std::exception &error)
//	{
//		std::cerr << "############ " << error.what() << std::endl;
//		msg += "Room does not exist :(\n";
//	}
//		
//	_clientManager->addDataToSend(client->getTCPSocket(), msg.c_str(), msg.size());
//}

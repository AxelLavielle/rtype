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
	BasicCmd		msg;
	std::string		handshake;
	Serialize		serializer;
	char			*msgSerialized;

	handshake = msgClient->getArg(0);
	std::cout << "[HandshakeSyn] : " << handshake << std::endl;
	msg.setCommandType(HANDSHAKE_SYN_ACK);
	msg.addArg(std::to_string(acknowledgementNumber));
	msg.addArg(std::to_string(std::stoi(handshake) + 1));
	msgSerialized = serializer.serialize(&msg);
	std::cout << "[HandshakeSyn] Sending : " << msg.getCommandArg() << std::endl;

	/*msg = "SYN-ACK [" + std::to_string(acknowledgementNumber) + "] & ";
	msg += std::to_string(std::stoi(handshake) + 1) + "\n";
	OutputDebugString(msg.c_str());
	*/
	_clientManager->addDataToSend(client->getTCPSocket(), msgSerialized, sizeof(msg));
}

void			CmdManager::cmdHandshakeAck(ServerClient *client, BasicCmd *msgClient,
											int acknowledgementNumber)
{
	std::string	handshake;

	handshake = msgClient->getArg(0);
	if (std::stoi(handshake) == acknowledgementNumber + 1)
	{
		//msg = "OK CONNECTED\n";
		client->setLogged(true);
		//_clientManager->addDataToSend(client->getTCPSocket(), msg.c_str(), msg.size());
	}
	else
	{
		closeSocket(client->getTCPSocket());
		_clientManager->removeClient(client);
	}
}
//
//void				CmdManager::cmdListRoom(ServerClient *client, const std::string &msgClient)
//{
//	std::string		msg;
//
//	(void)msgClient;
//	msg = "RoomList :\n" + _roomManager->getRoomListString() + "\n";
//	_clientManager->addDataToSend(client->getTCPSocket(), msg.c_str(), msg.size());
//}
//
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

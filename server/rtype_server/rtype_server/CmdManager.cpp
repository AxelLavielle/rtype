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
	close(client->getTCPSocket());
#endif
}

void								CmdManager::cmdCreateRoom(ServerClient *client, const std::string &msgClient)
{
	std::string						msg;
	int								newRoom;
	std::string						roomName;

	roomName = msgClient.substr(5);
	roomName.pop_back();
	newRoom = _roomManager->addRoom(roomName);
	msg = "Created |" + roomName + "| ---> Id = " + std::to_string(newRoom) + "\n";

	_clientManager->addDataToSend(client->getTCPSocket(), msg.c_str(), msg.size());
	_roomManager->addClientToRoom(client, newRoom);
}

void							CmdManager::cmdHandshakeSyn(ServerClient *client, const std::string &msgClient,
															int acknowledgementNumber)
{
	std::string					msg;
	std::string					handshake;

	handshake = msgClient.substr(4);
	handshake.pop_back();
	msg = "SYN-ACK [" + std::to_string(acknowledgementNumber) + "] & ";
	msg += std::to_string(std::stoi(handshake) + 1) + "\n";

	_clientManager->addDataToSend(client->getTCPSocket(), msg.c_str(), msg.size());
}

void			CmdManager::cmdHandshakeAck(ServerClient *client, const std::string &msgClient,
											int acknowledgementNumber)
{
	std::string	handshake;
	std::string	msg;

	handshake = msgClient.substr(4);
	handshake.pop_back();
	if (std::stoi(handshake) == acknowledgementNumber + 1)
	{
		msg = "OK CONNECTED\n";
		client->setLogged(true);
		_clientManager->addDataToSend(client->getTCPSocket(), msg.c_str(), msg.size());
	}
	else
	{
		closeSocket(client->getTCPSocket());
		_clientManager->removeClient(client);
	}
}

void				CmdManager::cmdListRoom(ServerClient *client, const std::string &msgClient)
{
	std::string		msg;

	(void)msgClient;
	msg = "RoomList :\n" + _roomManager->getRoomListString() + "\n";
	_clientManager->addDataToSend(client->getTCPSocket(), msg.c_str(), msg.size());
}

void			CmdManager::cmdJoinRoom(ServerClient *client, const std::string &msgClient)
{
	std::string roomName;
	std::string msg;
	Room		*r;

	roomName = msgClient.substr(5);
	roomName.pop_back();
	msg = "I want to join |" + roomName + "|\n";
	if (_roomManager->getRoomByName(roomName) != NULL)
	{
		r = _roomManager->getRoomByName(roomName);
		msg += "Room exist :D : " + r->getName() + "\n";
		_roomManager->addClientToRoom(client, _roomManager->getRoomByName(roomName)->getId());
	}
	else
		msg += "Room does not exist :(\n";
	_clientManager->addDataToSend(client->getTCPSocket(), msg.c_str(), msg.size());
}
#include "Server.hh"

Server::Server() : _cmdManager(&_clientManager, &_roomManager)
{
	_acknowledgementNumber = 666;
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

bool							Server::launch()
{
	std::vector<int>			socketsClients;
	int							clientSocketID = INVALID_SOCKET;
	std::vector<ClientMsg>		vectMsg;
	
	while (42)
	{
		_socketServerTCP.selectFds(_clientManager.getClientsTCPSockets());

		if ((clientSocketID = _socketServerTCP.acceptNewClient()) != -1)
		{
			_clientManager.addClient(clientSocketID);
		}

		vectMsg = _socketServerTCP.receiveData(_clientManager.getClients());
		processMsg(vectMsg);
		_clientManager.checkDisconnectedClients(_roomManager);

		_socketServerTCP.sendAllData(_clientManager.getClients());
		_clientManager.checkDisconnectedClients(_roomManager);
	}
	return (true);
}

//bool							Server::launchUDP()
//{
//	std::vector<int>			socketsClients;
//	int							clientSocketID = INVALID_SOCKET;
//	std::vector<ClientMsg>		vectMsg;
//	struct sockaddr_in			clientAddr;
//
//	while (42)
//	{
//		_socketServerUDP.selectFds(_clientManager.getClientsUDPSockets());
//
//		if ((clientSocketID = _socketServerUDP.acceptNewClient(&clientAddr)) != -1)
//		{
//			_clientManager.addClient(clientSocketID);
//			_clientManager.addDataToSend(clientSocketID, "Hello\n", 6);
//		}
//
//		vectMsg = _socketServerUDP.receiveData(_clientManager.getClients());
//		processMsg(vectMsg);
//		_clientManager.checkDisconnectedClients(_roomManager);
//
//		_socketServerUDP.sendAllData(_clientManager.getClients());
//		_clientManager.checkDisconnectedClients(_roomManager);
//	}
//	return (true);
//}

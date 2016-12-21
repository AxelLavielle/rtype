#include "CmdManager.hh"



CmdManager::CmdManager()
{
	_handKey = 42;
}

void CmdManager::setSocket(ASocketClient * socketClient)
{
	_socketClient = socketClient;
}

CmdManager::~CmdManager()
{
}

bool			CmdManager::launchGame()
{
	return (false);
}

RoomInfoCmd		*CmdManager::getRoomInfo()
{
	BasicCmd		*newCmd;
	ICommand		*cmd;

	newCmd = new BasicCmd();
	newCmd->setCommandType(GET_ROOM);
	_cmd.push_back(newCmd);
	if (!sendCmd())
		return (NULL);
	cmd = receiveCmd();
	if (cmd && cmd->getCommandName() == ROOM_INFO)
	{
		RoomInfoCmd		*tmpCmd;
		tmpCmd = static_cast<RoomInfoCmd* >(cmd);
		return (tmpCmd);
	}
	delete cmd;
	return (NULL);
}

bool	CmdManager::setStatus()
{
	BasicCmd		*newCmd;
	ICommand		*cmd;

	newCmd = new BasicCmd();
	newCmd->setCommandType(SET_STATUS);
	_cmd.push_back(newCmd);
	if (!sendCmd())
		return (false);
	cmd = receiveCmd();
	if (cmd && cmd->getCommandName() == BASIC_CMD && cmd->getCommandType() == REPLY_CODE)
	{
		BasicCmd		*tmpCmd;

		tmpCmd = static_cast<BasicCmd* >(cmd);
		if (static_cast<ReplyCodes>(std::stoi(tmpCmd->getArg(0))) == STATUS_CHANGED)
		{
			std::cout << "Room left" << std::endl;
			delete cmd;
			return (true);
		}
	}
	delete cmd;
	return (false);
}

bool	CmdManager::leaveRoom()
{
	BasicCmd		*newCmd;
	ICommand		*cmd;

	if (!_socketClient || !_socketClient->isConnected())
		return (false);
	newCmd = new BasicCmd();
	newCmd->setCommandType(LEAVE_ROOM);
	_socketClient->sendData(_serialize.serialize(newCmd), sizeof(*newCmd));
	cmd = receiveCmd();
	delete newCmd;
	if (cmd && cmd->getCommandName() == BASIC_CMD && cmd->getCommandType() == REPLY_CODE)
	{
		BasicCmd		*tmpCmd;

		tmpCmd = static_cast<BasicCmd* >(cmd);
		if (static_cast<ReplyCodes>(std::stoi(tmpCmd->getArg(0))) == LEFT_ROOM)
		{
			std::cout << "Room left" << std::endl;
			delete cmd;
			return (true);
		}
	}
	delete cmd;
	return (false);
}

bool	CmdManager::handshake()
{
	std::stringstream	ss;
	ICommand			*cmd = new BasicCmd();

	ss << _handKey;
	cmd->setCommandArg(ss.str());
	cmd->setCommandType(CmdType::HANDSHAKE_SYN);
	_cmd.push_back(cmd);
	if (!sendCmd())
		return (false);
	receiveCmd();
	return (true);
}

bool		CmdManager::createRoom(const std::string & rommName, const std::string & playerName)
{
	BasicCmd		*newCmd;
	ICommand		*cmd;

	if (!_socketClient || !_socketClient->isConnected())
		return (false);
	newCmd = new BasicCmd();
	newCmd->setCommandType(CREATE_ROOM);
	newCmd->addArg(rommName);
	newCmd->addArg(playerName);
	_cmd.push_back(newCmd);
	if (!sendCmd())
		return (false);
	cmd = receiveCmd();
	if (cmd->getCommandName() == BASIC_CMD && cmd->getCommandType() == REPLY_CODE)
	{
		BasicCmd		*tmpCmd;

		tmpCmd = static_cast<BasicCmd* >(cmd);
		if (static_cast<ReplyCodes>(std::stoi(tmpCmd->getArg(0))) == ROOM_CREATED)
		{
			std::cout << "CREATE ROOM OK" << std::endl;
			delete cmd;
			return (true);
		}
	}
	delete cmd;
	return (false);
}

bool	CmdManager::joinRoom(const int id, std::string & playerName)
{
	ICommand	*cmd;
	BasicCmd	*basicCmd = new BasicCmd();
	std::stringstream ss;

	ss << id;
	basicCmd->setCommandType(JOIN_ROOM);
	basicCmd->addArg(ss.str());
	basicCmd->addArg(playerName);
	_cmd.push_back(basicCmd);
	if (!sendCmd())
		return (false);
	cmd = receiveCmd();
	if (cmd && cmd->getCommandName() == BASIC_CMD && cmd->getCommandType() == REPLY_CODE)
	{
		BasicCmd		*tmpCmd;

		tmpCmd = static_cast<BasicCmd* >(cmd);
		if (static_cast<ReplyCodes>(std::stoi(tmpCmd->getArg(0))) == ROOM_JOINED)
		{
			std::cout << "JOIN ROOM OK" << std::endl;
			delete cmd;
			return (true);
		}
	}
	delete cmd;
	return (false);
}

ListRoomCmd	*CmdManager::getRoomList()
{
	ListRoomCmd			*resCmd;
	ICommand			*cmd;
	BasicCmd			*basicCmd = new BasicCmd();
	char				*res;

	basicCmd->setCommandType(GET_ROOM_LIST);
	_cmd.push_back(basicCmd);
	if (!sendCmd())
		return (false);

	//A modifier
	if (!(res = _socketClient->receiveData()))
		return (NULL);
	cmd = _serialize.unserializeCommand(res);
	resCmd = static_cast<ListRoomCmd*>(cmd);

	return (resCmd);
}

bool		CmdManager::confirmHandshake(ICommand *cmd)
{
	BasicCmd			*basicCmd;
	BasicCmd			*newCmd;
	std::stringstream	ss;
	int					key1;
	int					key2;

	basicCmd = static_cast<BasicCmd*>(cmd);
	key1 = std::stoi(basicCmd->getArg(0));
	key2 = std::stoi(basicCmd->getArg(1));
	if (key2 == _handKey + 1)
	{
		newCmd = new BasicCmd();
		ss << key1 + 1;
		newCmd->setCommandArg(ss.str());
		newCmd->setCommandType(CmdType::HANDSHAKE_ACK);
		_cmd.push_back(newCmd);
		if (!sendCmd())
			return (false);
	}
	else
	{
		std::cerr << "ERROR: handshake" << std::endl;
		return (false);
	}
	return (true);
}

bool		CmdManager::sendCmd()
{
	std::vector<ICommand*>::iterator	it;
	if (!_socketClient || !_socketClient->isConnected())
		return (false);
	it = _cmd.begin();
	while (it != _cmd.end())
	{
		if (!_socketClient->sendData(_serialize.serialize(*it), sizeof(*(*it))))
		{
			std::cerr << "ERROR: cant not send data" << std::endl;
			return (false);
		}
		delete (*it);
		it = _cmd.erase(it);
	}
	return (true);
}

ICommand	*CmdManager::receiveCmd()
{
	ICommand			*cmd;
	char				*res;

	//Select a faire
	if (!(res = _socketClient->receiveData()))
		return (NULL);
	cmd = _serialize.unserializeCommand(res);
	switch (cmd->getCommandName())
	{
	case (BASIC_CMD):
		if (cmd->getCommandType() == HANDSHAKE_SYN_ACK)
			confirmHandshake(cmd);
		break;
	case (ROOM_LIST):
		getRoomList();
		break;
	case (REPLY_CODE):
		BasicCmd	*newCmd;

		newCmd = static_cast<BasicCmd* >(cmd);
		return (newCmd);
		break;
	default:
	  break;
	}
	return (cmd);
}

bool CmdManager::newCmd(ICommand *cmd)
{
	_cmd.push_back(cmd);
	return (true);
}

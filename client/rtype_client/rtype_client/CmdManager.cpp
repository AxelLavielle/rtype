#include "CmdManager.hh"

CmdManager::CmdManager()
{
	_handKey = 42;
	_id = -1;
	_roomInfo = NULL;
	_roomList = NULL;
	_wait = UNDERSTOOD;
	_socketClient = NULL;
	_error = -1;
}

void	CmdManager::sendQuit()
{
	BasicCmd	*cmd;

	cmd = new BasicCmd();

	cmd->setCommandType(QUIT_GAME);
	_mutex.lock();
	_cmd.push_back(cmd);
	_mutex.unlock();
}

void CmdManager::setSocket(ASocketClient * socketClient)
{
	_mutexSocket.lock();
	_mutex.lock();
	_socketClient = socketClient;
	_error = -1;
	_wait = UNDERSTOOD;
	_mutex.unlock();
	_mutexSocket.unlock();
}

void CmdManager::setUDPSocket(ASocketClient * socket)
{
	_socketClientUDP = socket;
}

CmdManager::~CmdManager()
{
}

int				CmdManager::getLatsReply()
{
	int			res;

	_mutex.lock();
	res = _error;
	_error = -1;
	_mutex.unlock();
	return (res);
}

bool			CmdManager::isWaiting()
{
	_mutex.lock();
	if (_wait != UNDERSTOOD)
	{
		_mutex.unlock();
		return (true);
	}
	_mutex.unlock();
	return (false);
}

int				CmdManager::getId()
{
	int res;

	_mutex.lock();
	res = _id;
	_id = -1;
	_mutex.unlock();
	return (res);
}

bool			CmdManager::sendLaunchGame(const int id)
{
	BasicCmd	*cmd;
	std::stringstream	ss;

	ss << id;
	cmd = new BasicCmd();
	cmd->setCommandType(REPLY_CODE);
	cmd->addArg(ss.str());
	_cmd.push_back(cmd);
	return (true);
}

bool			CmdManager::sendInput(const int id, const std::string &key)
{
	InputCmd	*newCmd;

	newCmd = new InputCmd();
	newCmd->setId(id);
	newCmd->setKey(key);
	_cmd.push_back(newCmd);
	if (!sendUDPCmd())
		return (false);
	return (true);
}

RoomInfoCmd		*CmdManager::getRoomInfo()
{
	RoomInfoCmd		*res;

	_mutex.lock();
	res = _roomInfo;
	_mutex.unlock();
	return (res);
}

bool	CmdManager::setStatus()
{
	BasicCmd		*newCmd;
	ICommand		*cmd;

	newCmd = new BasicCmd();
	newCmd->setCommandType(SET_STATUS);
	_mutex.lock();
	_cmd.push_back(newCmd);
	_mutex.unlock();
	//_wait = STATUS_CHANGED;
	return (false);
}

bool	CmdManager::leaveRoom()
{
	BasicCmd		*newCmd;
	ICommand		*cmd;

	newCmd = new BasicCmd();
	newCmd->setCommandType(LEAVE_ROOM);
	_mutex.lock();
	_cmd.push_back(newCmd);
	_mutex.unlock();
	_wait = LEFT_ROOM;
	return (false);
}

bool	CmdManager::handshake()
{
	std::stringstream	ss;
	ICommand			*cmd = new BasicCmd();
	ICommand			*oldCmd;

	ss << _handKey;
	cmd->setCommandArg(ss.str());
	cmd->setCommandType(CmdType::HANDSHAKE_SYN);
	_mutex.lock();
	_cmd.push_back(cmd);
	_mutex.unlock();
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
	_mutex.lock();
	_cmd.push_back(newCmd);
	_mutex.unlock();
	_wait = ROOM_CREATED;
	return (true);
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
	std::cout << "Player name = " << basicCmd->getArg(1) << std::endl;
	_mutex.lock();
	_cmd.push_back(basicCmd);
	_mutex.unlock();
	_wait = ROOM_JOINED;
	return (false);
}

void	CmdManager::sendRoomList()
{
	ListRoomCmd			*resCmd;
	BasicCmd			*basicCmd = new BasicCmd();

	basicCmd->setCommandType(GET_ROOM_LIST);
	_mutex.lock();
	_cmd.push_back(basicCmd);
	_mutex.unlock();
}

ListRoomCmd * CmdManager::getRoomList()
{
	ListRoomCmd			*res;

	_mutex.lock();
	res = _roomList;
	_mutex.unlock();
	return (res);
}

bool		CmdManager::confirmHandshake(ICommand *cmd)
{
	BasicCmd			*basicCmd;
	BasicCmd			*newCmd;
	std::stringstream	ss;
	int					key1;
	int					key2;

	if (!cmd || cmd->getCommandName() != BASIC_CMD || cmd->getCommandType() != HANDSHAKE_SYN_ACK)
		return (false);
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
	}
	else
	{
		std::cerr << "ERROR: handshake" << std::endl;
		return (false);
	}
	return (true);
}

EndGameCmd	*CmdManager::receiveEndGame()
{
	EndGameCmd	*end;

	ICommand			*cmd;
	char				*res;

	_mutexSocket.lock();
	if (!_socketClient || !(res = _socketClient->receiveData()))
	{
		_mutexSocket.unlock();
		return (NULL);
	}
	_mutexSocket.unlock();
	cmd = _serialize.unserializeCommand(res);
	delete[] res;
	if (cmd && cmd->getCommandName() == END_GAME)
	{
		std::cout << "End Received" << std::endl;
		end = static_cast<EndGameCmd *>(cmd);
		return (end);
	}
	delete cmd;
	return (NULL);
}

bool		CmdManager::sendCmd()
{
	std::vector<ICommand*>::iterator	it;
	char								*res;

	//_mutex.lock();
	//if (_wait != UNDERSTOOD)
	//{
	//	_mutex.unlock();
	//	return (false);
	//}
	//_mutex.unlock();

	_mutexSocket.lock();
	if (!_socketClient || !_socketClient->isConnected())
	{
		_mutexSocket.unlock();
		return (false);
	}
	_mutexSocket.unlock();
	it = _cmd.begin();
	while (it != _cmd.end())
	{
		_mutex.lock();
		res = _serialize.serialize(*it);
		if (!_socketClient->sendData(res))
		{
			std::cerr << "ERROR: cant not send data" << std::endl;
			_mutex.unlock();
			delete[] res;
			return (false);
		}
		delete[] res;
		delete (*it);
		it = _cmd.erase(it);
		_mutex.unlock();
	}
	return (true);
}

bool		CmdManager::sendUDPCmd()
{
	std::vector<ICommand*>::iterator	it;
	char								*res;

	_mutexSocket.lock();
	if (!_socketClientUDP || !_socketClientUDP->isConnected())
	{
		_mutexSocket.unlock();
		return (false);
	}
	_mutexSocket.unlock();
	it = _cmd.begin();
	while (it != _cmd.end())
	{
		res = _serialize.serialize(*it);
		if (!_socketClientUDP->sendData(res))
		{
			std::cerr << "ERROR: cant not send data" << std::endl;
			return (false);
		}
		delete[] res;
		delete (*it);
		it = _cmd.erase(it);
	}
	return (true);
}

IEntity		*CmdManager::receiveUDPCmd()
{
	IEntity	*entity;
	char	*res;

	entity = NULL;
	_mutexSocket.lock();
	if (!_socketClientUDP || !_socketClientUDP->isConnected())
	{
		_mutexSocket.unlock();
		return (NULL);
	}
	_mutexSocket.unlock();
	res = _socketClientUDP->receiveData();
	entity = Serialize::unserializeEntity(res);
	if (res != NULL)
		delete[] res;
	return (entity);
}

ICommand	*CmdManager::receiveCmd(const int sec, const int usec)
{
	ICommand			*cmd;
	char				*res;

	_mutexSocket.lock();
	if (!_socketClient || !(res = _socketClient->receiveData()))
	{
		_mutexSocket.unlock();
		return (NULL);
	}
	_mutexSocket.unlock();
	cmd = _serialize.unserializeCommand(res);
	delete[] res;
	//std::cout << "COMMAND RECEIVED : " << cmd->getCommandName() << "COMMAND TYPE : " << cmd->getCommandType() << std::endl;
	switch (cmd->getCommandName())
	{

	case (BASIC_CMD):
		if (cmd->getCommandType() == HANDSHAKE_SYN_ACK)
			confirmHandshake(cmd);
		else if (cmd->getCommandType() == REPLY_CODE)
		{
			BasicCmd		*tmpCmd;

			tmpCmd = static_cast<BasicCmd*>(cmd);
			if (static_cast<ReplyCodes>(std::stoi(tmpCmd->getArg(0))) == _wait)
			{
				_mutex.lock();
				_error = 0;
				_wait = UNDERSTOOD;
				_mutex.unlock();
			}
			else if (static_cast<ReplyCodes>(std::stoi(tmpCmd->getArg(0))) >= NOT_IN_LOBBY
				&& static_cast<ReplyCodes>(std::stoi(tmpCmd->getArg(0))) <= ROOM_NOT_EXIST)
			{
				_mutex.lock();
				_error = 1;
				_wait = UNDERSTOOD;
				_mutex.unlock();
			}
		}
		else if (cmd->getCommandType() == LAUNCH_GAME)
		{
			BasicCmd		*basicCmd;

			basicCmd = static_cast<BasicCmd*>(cmd);
			_mutex.lock();
			_id = std::stoi(basicCmd->getArg(1));
			_mutex.unlock();
		}
		else if (cmd->getCommandType() == UPDATE_ROOM)
		{
			BasicCmd		*newCmd;
			ICommand		*cmd;

			newCmd = new BasicCmd();
			newCmd->setCommandType(GET_ROOM);
			_mutex.lock();
			_cmd.push_back(newCmd);
			_mutex.unlock();
		}
		break;
	case (ROOM_LIST):
		_mutex.lock();
		_roomList = static_cast<ListRoomCmd* >(cmd);
		_mutex.unlock();
		return (NULL);
		break;
	case (ROOM_INFO):
		_mutex.lock();
		_roomInfo = static_cast<RoomInfoCmd*>(cmd);
		_mutex.unlock();
		return (NULL);
		break;
	default:
	  break;
	}
	delete cmd;
	return (NULL);
}

bool CmdManager::newCmd(ICommand *cmd)
{
	_cmd.push_back(cmd);
	return (true);
}

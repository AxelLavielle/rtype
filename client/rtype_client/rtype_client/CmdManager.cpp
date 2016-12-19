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

bool	CmdManager::handshake()
{
	std::stringstream	ss;
	ICommand			*cmd = new BasicCmd();
	char				*res;

	ss << _handKey;
	cmd->setCommandArg(ss.str());
	cmd->setCommandType(CmdType::HANDSHAKE_SYN);
	res = _serialize.serialize(cmd);
	_socketClient->sendData(res, sizeof(*cmd));
	delete cmd;
	receiveCmd();
	return (true);
}

ListRoomCmd	*CmdManager::getRoomList()
{
	ListRoomCmd			*resCmd;
	ICommand			*cmd;
	BasicCmd			basicCmd;
	char				*res;

	basicCmd.setCommandType(GET_ROOM_LIST);
	_socketClient->sendData(_serialize.serialize(&basicCmd), sizeof(basicCmd));
	if (!(res = _socketClient->receiveData()))
		return (NULL);
	cmd = _serialize.unserializeCommand(res);
	resCmd = static_cast<ListRoomCmd*>(cmd);
	std::cout << resCmd->getRoom(0).first << std::endl;
	return (resCmd);
}

void		CmdManager::confirmHandshake(const char *msg, ICommand *cmd)
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
		_socketClient->sendData(_serialize.serialize(newCmd), sizeof(*newCmd));
	}
	else
		std::cerr << "ERROR: handshake" << std::endl;
}

ICommand	*CmdManager::receiveCmd()
{
	ICommand			*cmd;
	char				*res;

	if (!(res = _socketClient->receiveData()))
		return (NULL);
	cmd = _serialize.unserializeCommand(res);
	switch (cmd->getCommandName())
	{
	case (BASIC_CMD):
		if (cmd->getCommandType() == HANDSHAKE_SYN_ACK)
			confirmHandshake(res, cmd);
		break;
	case (ROOM_LIST):
		getRoomList();
		break;
	default:
	  break;
	}
	return (cmd);
}

bool CmdManager::newCmd(const std::string & cmd)
{
  (void)cmd;
	//Not implemented
	return (true);
}

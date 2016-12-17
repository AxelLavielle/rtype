#include "CmdManager.hh"



CmdManager::CmdManager()
{
	_handKey = 4242;
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
	cmd->setCommandType(CmdType::SYN);
	res = _serialize.serialize(cmd);
	_socketClient->sendData(res);
	delete cmd;
	receiveCmd();
	return (true);
}

ACommand	*CmdManager::receiveCmd()
{
	ICommand			*cmd;
	char				*res;

	res = _socketClient->receiveData();
	cmd = _serialize.unserializeCommand(res);
	return (NULL);
}

bool CmdManager::newCmd(const std::string & cmd)
{
  (void)cmd;
	//Not implemented
	return (true);
}

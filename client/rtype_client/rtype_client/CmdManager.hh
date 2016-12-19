#pragma once

#include <string>
#include <sstream>
#include "CmdEnum.hh"
#include "SocketClientTCP.hh"
#include "Serialize.hh"
#include "BasicCmd.hh"

class CmdManager
{
public:
	CmdManager();
	~CmdManager();
	bool handshake();
	ICommand * receiveCmd();
	bool newCmd(const std::string & cmd);
	void setSocket(ASocketClient * sosket);

private:
	ASocketClient		*_socketClient;
	Serialize			_serialize;
	int					_handKey;

	void confirmHandshake(const char * msg, ICommand * cmd);
};


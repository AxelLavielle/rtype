#pragma once

#include <string>
#include <sstream>
#include <sstream>
#include "CmdEnum.hh"
#include "SocketClientTCP.hh"
#include "Serialize.hh"
#include "BasicCmd.hh"
#include "ListRoomCmd.hh"

class CmdManager
{
public:
	CmdManager();
	~CmdManager();
	bool setStatus();
	bool leaveRoom();
	bool handshake();
	bool createRoom(const std::string & rommName, const std::string & playerName);
	bool joinRoom(const int id, std::string & playerName);
	ListRoomCmd *getRoomList();
	ICommand * receiveCmd();
	bool newCmd(const std::string & cmd);
	void setSocket(ASocketClient * sosket);

private:
	ASocketClient		*_socketClient;
	Serialize			_serialize;
	int					_handKey;

	void confirmHandshake(const char * msg, ICommand * cmd);
};


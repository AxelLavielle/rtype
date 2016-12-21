#pragma once

#include <string>
#include <sstream>
#include <sstream>
#include "CmdEnum.hh"
#include "SocketClientTCP.hh"
#include "Serialize.hh"
#include "BasicCmd.hh"
#include "ListRoomCmd.hh"
#include "RoomInfoCmd.hh"

class CmdManager
{
public:
	CmdManager();
	~CmdManager();
	bool launchGame();
	RoomInfoCmd * getRoomInfo();
	bool setStatus();
	bool leaveRoom();
	bool handshake();
	bool createRoom(const std::string & rommName, const std::string & playerName);
	bool joinRoom(const int id, std::string & playerName);
	ListRoomCmd *getRoomList();
	ICommand * receiveCmd();
	bool newCmd(ICommand *command);
	void setSocket(ASocketClient * sosket);

private:
	ASocketClient		*_socketClient;
	Serialize			_serialize;
	int					_handKey;
	std::vector<ICommand*>	_cmd;

	bool confirmHandshake(ICommand * cmd);
	bool sendCmd();
};


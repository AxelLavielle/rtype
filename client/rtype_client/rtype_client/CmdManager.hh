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
#include "IEntity.hpp"

class CmdManager
{
public:
	CmdManager();
	~CmdManager();
	bool sendInput(const std::string & key);
	int launchGame();
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
	std::vector<IEntity* >	_entity;

	bool confirmHandshake(ICommand * cmd);
	bool sendCmd();
};


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
	bool sendLaunchGame(const int id);
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
	void setUDPSocket(ASocketClient *socket);
	bool sendCmd();
	bool sendUDPCmd();

private:
	ASocketClient		*_socketClient;
	ASocketClient		*_socketClientUDP;
	Serialize			_serialize;
	int					_handKey;
	std::vector<ICommand*>	_cmd;

	bool confirmHandshake(ICommand * cmd);
};


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
#include "Mutex.hh"

class CmdManager
{
public:
	CmdManager();
	~CmdManager();
	int getLatsReply();
	bool isWaiting();
	int getId();
	bool sendLaunchGame(const int id);
	bool sendInput(const int id, const std::string & key);
	RoomInfoCmd * getRoomInfo();
	bool setStatus();
	bool leaveRoom();
	bool handshake();
	bool createRoom(const std::string & rommName, const std::string & playerName);
	bool joinRoom(const int id, std::string & playerName);
	void sendRoomList();
	ListRoomCmd *getRoomList();
	ICommand * receiveCmd(const int sec = 0, const int usec = 100);
	bool newCmd(ICommand *command);
	void setMutexSocket(AMutex * mutex);
	void setSocket(ASocketClient * sosket);
	void setUDPSocket(ASocketClient *socket);
	bool sendCmd();
	bool sendUDPCmd();

	IEntity * receiveUDPCmd();

private:
	ASocketClient			*_socketClient;
	ASocketClient			*_socketClientUDP;
	Serialize				_serialize;
	int						_handKey;
	std::vector<ICommand*>	_cmd;
	std::vector<ICommand *>	_cmdReceive;
	bool confirmHandshake(ICommand * cmd);
	RoomInfoCmd				*_roomInfo;
	int						_id;
	ListRoomCmd				*_roomList;
	ReplyCodes				_wait;
	int						_error;
	Mutex					_mutex;
	AMutex					*_mutexSocket;
};


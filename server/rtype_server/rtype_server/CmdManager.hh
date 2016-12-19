#pragma once

#include "ServerClient.hh"
#include "ClientManager.hh"
#include "RoomManager.hh"
#include "ASocketServer.hh"
#include "BasicCmd.hh"
#include "ACommand.hh"
#include "ListRoomCmd.hh"

class CmdManager
{
private:
	ClientManager	*_clientManager;
	RoomManager		*_roomManager;
	void			closeSocket(int);


public:
	CmdManager(ClientManager *, RoomManager *);
	~CmdManager();

	void			cmdCreateRoom(ServerClient *, BasicCmd *);
	void			cmdHandshakeSyn(ServerClient *, BasicCmd *, const int);
	void			cmdHandshakeAck(ServerClient *, BasicCmd *, const int);
	void			cmdListRoom(ServerClient *, BasicCmd *);
	void			cmdJoinRoom(ServerClient *, BasicCmd *);

	void			cmdLaunchGame(const std::vector<ServerClient *> &, const int);

};

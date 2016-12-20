#pragma once

#include "ServerClient.hh"
#include "ClientManager.hh"
#include "RoomManager.hh"
#include "ASocketServer.hh"
#include "BasicCmd.hh"
#include "ACommand.hh"
#include "ListRoomCmd.hh"
#include "AMutex.hh"

class CmdManager
{
private:
	ClientManager	*_clientManager;
	RoomManager		*_roomManager;
	AMutex			*_mutex;
	void			closeSocket(int);

public:
	CmdManager(ClientManager *, RoomManager *);
	~CmdManager();

	void			setMutex(AMutex *);
	void			cmdCreateRoom(ServerClient *, BasicCmd *);
	void			cmdHandshakeSyn(ServerClient *, BasicCmd *, const int);
	void			cmdHandshakeAck(ServerClient *, BasicCmd *, const int);
	void			cmdListRoom(ServerClient *, BasicCmd *);
	void			cmdRoomInfo(ServerClient *, BasicCmd *);
	void			cmdJoinRoom(ServerClient *, BasicCmd *);
	void			cmdLeaveRoom(ServerClient *, BasicCmd *);
	void			cmdSetStatus(ServerClient *, BasicCmd *);

	void			cmdLaunchGame(const std::vector<ServerClient *> &, const int);

};

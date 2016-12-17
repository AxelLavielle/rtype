#pragma once

#include "SocketServerTCP.hh"
#include "SocketServerUDP.hh"
#include "ClientManager.hh"
#include "RoomManager.hh"
#include "CmdManager.hh"

class CmdManager;

class Server
{
private:
	SocketServerTCP	_socketServerTCP;
	SocketServerUDP	_socketServerUDP;
	ClientManager	_clientManager;
	RoomManager		_roomManager;
	CmdManager		_cmdManager;
	int				_acknowledgementNumber;

	void			processMsg(const std::vector<ClientMsg> &);

public:
	Server();
	~Server();

	bool	init();
	bool	launch();
	bool	launchUDP();
	void	closeSocket(int);
};
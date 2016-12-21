#pragma once

#include "SocketServerTCP.hh"
#include "SocketServerUDP.hh"
#include "ClientManager.hh"
#include "RoomManager.hh"
#include "CmdManager.hh"
#include "BasicCmd.hh"
#include "AMutex.hh"
#include "Thread.hh"
#include "ThreadPool.hh"
#include "Mutex.hh"
#include "Game.hh"

class CmdManager;

class Server
{
private:
	SocketServerTCP	_socketServerTCP;
	SocketServerUDP	_socketServerUDP;
	ClientManager	_clientManager;
	RoomManager		_roomManager;
	CmdManager		_cmdManager;
	ThreadPool		_pool;
	AMutex			*_mutex;
	Game			_gameManager;
	int				_acknowledgementNumber;

	void			processMsg(const std::vector<ClientMsg> &);
	void			processBasicCmd(ServerClient *, BasicCmd *);
	void			processGames();
	void			processUDPMessages(const std::vector<UDPClientMsg> &);
	void			checkNewUDPClients(const std::vector<UDPClientMsg> &);
	void			checkRoomsReadyToLaunch();

public:
	Server();
	~Server();

	bool	init();
	bool	launch();
	bool	TCPLoop();
	bool	UDPLoop();
};
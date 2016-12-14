#pragma once

#include "ClientManager.hh"
#include "SocketServerTCP.hh"
#include <vector>

class Server
{
private:
	ASocketServer	*_socketServer;
	ClientManager	_clientManager;

	void			processMsg(const std::vector<ClientMsg> &);

public:
	Server();
	~Server();

	bool	init();
	bool	launch();
};


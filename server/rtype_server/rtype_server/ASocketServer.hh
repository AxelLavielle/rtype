#pragma once

#include <string>
#include <vector>
#include "ServerClient.hh"
#include "ISocket.hpp"
#include "ICommand.hpp"
#include "Serialize.hh"

class SocketAddress;
//class ServerClient;

typedef std::pair<int, SocketAddress *>			NewClientInfo;
typedef std::pair<ServerClient *, ICommand *>	ClientMsg;

class ASocketServer : public ISocket
{
protected:
	int				_socketServerID;
	int				_port;

public:
	ASocketServer();
	virtual ~ASocketServer();

	virtual bool				init(const std::string &, const int) = 0;
	virtual bool				closure();
	virtual bool				sendAllData(std::vector<ServerClient *> &) = 0;
	virtual bool				launch() = 0;
};


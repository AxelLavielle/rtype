#pragma once

#ifdef _WIN32

# include <winsock2.h>
# include <ws2tcpip.h>
# include <windows.h>
# pragma comment(lib, "Ws2_32.lib")

#elif __linux__

# include <sys/select.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <unistd.h>
# include <stdio.h>
# include <netdb.h>

#endif

#include <string>
#include <vector>
#include "ServerClient.hh"
#include "ISocket.hpp"

typedef std::pair<ServerClient *, std::string> ClientMsg;

class ASocketServer : public ISocket
{
protected:
	int				_socketServerID;

public:
	ASocketServer();
	virtual ~ASocketServer();

	virtual bool						init(const std::string &, int) = 0;
	virtual bool						sendAllData(std::vector<ServerClient *> &) = 0;
	virtual std::vector<ClientMsg>		receiveData(std::vector<ServerClient *> &) = 0;
	virtual bool						launch() = 0;
//	virtual int							acceptNewClient() = 0;
	virtual bool						closure();
	virtual int							selectFds(const std::vector<int> &) = 0;
};


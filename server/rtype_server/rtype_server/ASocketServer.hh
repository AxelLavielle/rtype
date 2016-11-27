#pragma once

#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#pragma comment(lib, "Ws2_32.lib")

class ASocketServer
{
protected:
	int				_socketServerID;

public:
	ASocketServer();
	virtual ~ASocketServer();

	virtual bool	init(const std::string &, int) = 0;
	virtual bool	sendData(const char *data) = 0;
	virtual char	*receiveData() = 0;
	virtual bool	close();
	virtual bool	launch() = 0;
};


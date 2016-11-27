#pragma once

#include "ISocket.hpp"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

#pragma comment(lib, "Ws2_32.lib")

class ASocketClient : public ISocket
{
public:
	ASocketClient();
	virtual ~ASocketClient();

	virtual bool	init(const std::string &, int) = 0;
	virtual bool	sendData(const char *) = 0;
	virtual char	*receiveData() = 0;
	virtual bool	close();

protected:
	int				_port;
	int				_socketClientId;
	SOCKET			_connectSocket;
};


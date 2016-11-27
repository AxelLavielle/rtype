#pragma once

#define DEFAULT_BUFLEN 512

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include "ASocketClient.hh"

class SocketClientTCP : public ASocketClient
{
public:
	SocketClientTCP();
	virtual ~SocketClientTCP();

	virtual bool	init(const std::string &, int);
	virtual bool	sendData(const char *);
	virtual char	*receiveData();
	virtual bool	close();
	virtual bool	connectToServer();

private:
	WSADATA			_wsaData;
	SOCKET			_connectSocket;
	struct addrinfo	*_result;
	struct addrinfo *_ptr;
};


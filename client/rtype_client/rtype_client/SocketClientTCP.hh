#pragma once

#include "ASocketClient.hh"

class SocketClientTCP : public ASocketClient
{
public:
	SocketClientTCP();
	virtual ~SocketClientTCP();

	virtual bool	init(const std::string &, int);
	virtual bool	sendData(const char *);
	virtual char	*receiveData();
	bool			connect();

private:
	WSADATA			_wsaData;
	SOCKET			_connectSocket;
	struct addrinfo	*_result;
	struct addrinfo *_ptr;
};


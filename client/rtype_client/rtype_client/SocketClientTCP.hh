#pragma once

#define DEFAULT_BUFLEN 512
#include "ASocketClient.hh"

class SocketClientTCP : public ASocketClient
{
public:
	SocketClientTCP();
	virtual ~SocketClientTCP();

	virtual bool	init(const std::string &, int);
	virtual bool	sendData(const char *);
	virtual char	*receiveData();
	bool			connectToServer();

private:
	WSADATA			_wsaData;
	struct addrinfo	*_result;
	struct addrinfo *_ptr;
};


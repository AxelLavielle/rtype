#pragma once

# define TCP_BUFLEN 65471

#ifdef _WIN32
	# include <winsock2.h>
	# include <windows.h>
	# include <ws2tcpip.h>
	# include <iphlpapi.h>
#elif __linux__
	# include <stdlib.h>
	# include <sys/socket.h>
	# include <arpa/inet.h>
	# include <unistd.h>
#endif

#include <string.h>
#include "ASocketClient.hh"
class					SocketClientTCP : public ASocketClient
{
public:
	SocketClientTCP();
	virtual ~SocketClientTCP();

	virtual bool		init(const std::string &, int);
	virtual bool		sendData(const char *);
	virtual char		*receiveData();
	virtual bool		closure();
	virtual bool		connectToServer();

private:
#ifdef _WIN32
	WSADATA				_wsaData;
	SOCKET				_connectSocket;
	struct addrinfo		*_result;
	struct addrinfo		*_ptr;
#elif __linux__
	int					_sock;
	struct sockaddr_in	_server;
#endif
};


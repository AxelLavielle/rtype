#pragma once

# define UDP_BUFLEN (1448)

#ifdef _WIN32
	# include <winsock2.h>
	# include <Ws2tcpip.h>
#elif __linux__
	# include <arpa/inet.h>
	# include <sys/socket.h>
#endif

#include "ASocketClient.hh"

class SocketClientUDP : public ASocketClient
{
public:
	SocketClientUDP();
	virtual ~SocketClientUDP();

	virtual bool		init(const std::string &, int);
	virtual bool		sendData(const char *);
	virtual char		*receiveData();
	virtual bool		close();
	virtual bool		connectToServer();

private:
	int					_sock;
	struct sockaddr_in	_siOther;
#ifdef __linux__
	struct sockaddr_in	_siMe;
#endif
};


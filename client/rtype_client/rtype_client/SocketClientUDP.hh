#pragma once

# define UDP_BUFLEN (1448)

#ifdef _WIN32
	# include <winsock2.h>
	# include <Ws2tcpip.h>
#elif __linux__
	# include <arpa/inet.h>
	# include <sys/socket.h>
	# include <unistd.h>
#elif __APPLE__
	# include <arpa/inet.h>
	# include <sys/socket.h>
	# include <unistd.h>
#endif

# include <cstring>
# include "ASocketClient.hh"
# include "Player.hh"
# include "Serialize.hh"

class SocketClientUDP : public ASocketClient
{
public:
	SocketClientUDP();
	virtual ~SocketClientUDP();

	virtual bool		init(const std::string &, const int);
	virtual bool		sendData(const char *);
	virtual bool sendData(const char * data, const int datasize);
	virtual char * receiveData(const int secTimeOut, const int usecTimeOut);
	virtual char		*receiveData();
	virtual bool		closure();
	virtual bool		connectToServer();

private:
	int					_sock;
	struct sockaddr_in	_siOther;
};

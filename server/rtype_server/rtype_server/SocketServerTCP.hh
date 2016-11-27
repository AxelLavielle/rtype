#ifndef SOCKET_SERVER_TCP_HH_
# define SOCKET_SERVER_TCP_HH_

#include "ASocketServer.hh"

class SocketServerTCP : public ASocketServer
{
private:
	struct addrinfo *_addrSocket;

public:
	SocketServerTCP();
	~SocketServerTCP();

	bool			init(const std::string &, int);
	bool			launch();
	int				acceptNewClient();
	virtual bool	sendData(const char *data);
	virtual char	*receiveData();
};


#endif /* SOCKET_SERVER_TCP_HH_ */
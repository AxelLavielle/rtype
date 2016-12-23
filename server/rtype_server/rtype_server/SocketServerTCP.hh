#pragma once

#ifdef __linux__
# define INVALID_SOCKET (-1)
# define SOCKET_ERROR	(-1)
#endif

#include "ASocketServer.hh"

class SocketServerTCP : public ASocketServer
{
private:
	struct sockaddr_in	_addrSocket;
	int					_fdMax;
	fd_set				_readfds;
	fd_set				_writefds;

	void				displayError(const std::string &);

public:
	SocketServerTCP();
	virtual ~SocketServerTCP();

	virtual bool					init(const std::string &, const int);
	virtual bool					launch();
	virtual bool					sendAllData(std::vector<ServerClient *> &);
	std::vector<ClientMsg>			receiveData(std::vector<ServerClient *> &);
	int								selectFds(const std::vector<int> &);
	NewClientInfo					acceptNewClient();
};

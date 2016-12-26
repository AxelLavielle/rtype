#pragma once

#include "ASocketServer.hh"

class SocketServerUDP : public ASocketServer
{
private:
	struct sockaddr_in	_addrSocket;
	fd_set				_readfds;
	fd_set				_writefds;
	void				displayError(const std::string &);

public:
	SocketServerUDP();
	virtual ~SocketServerUDP();

	virtual bool						init(const std::string &, const int);
	virtual bool						launch();
	virtual bool						sendAllData(std::vector<ServerClient *> &);
	std::vector<ICommand *>				receiveData();
	int									selectFds();
};


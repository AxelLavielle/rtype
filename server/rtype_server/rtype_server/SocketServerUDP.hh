#pragma once

#ifdef __linux__
# define INVALID_SOCKET (-1)
# define SOCKET_ERROR	(-1)
#endif

#include "ASocketServer.hh"

typedef std::pair<struct sockaddr_in *, ICommand *> UDPClientMsg;

class SocketServerUDP : public ASocketServer
{
private:
	int					_socketFd;
	int					_port;
	struct sockaddr_in	_addrSocket;
	void				displayError(const std::string &);

public:
	SocketServerUDP();
	virtual ~SocketServerUDP();

	virtual bool					init(const std::string &, const int);
	virtual bool					launch();
	virtual bool					sendAllData(std::vector<ServerClient *> &);
	virtual std::vector<UDPClientMsg>			receiveData();
	int						acceptNewClient(struct sockaddr_in *);
	virtual int				selectFds(const std::vector<int> &);

};


#pragma once

#include "ISocket.hpp"

#ifdef _WIN32
	#pragma comment(lib, "Ws2_32.lib")
#endif

class ASocketClient : public ISocket
{
public:
	ASocketClient();
	virtual ~ASocketClient();

	virtual bool	init(const std::string &, const int) = 0;
	virtual bool	closure() = 0;
	virtual bool	sendData(const char *, const int datasize) = 0;
	virtual char	*receiveData() = 0;
	virtual bool	connectToServer() = 0;
	virtual bool	isConnected() const;

protected:
	int				_port;
	int				_socketClientId;
	bool			_connected;
};


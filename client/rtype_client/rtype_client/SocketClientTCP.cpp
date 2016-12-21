#include "SocketClientTCP.hh"

SocketClientTCP::SocketClientTCP()
{

}


SocketClientTCP::~SocketClientTCP()
{

}

bool				SocketClientTCP::init(const std::string &addr, const int port)
{
	if (_port == -1)
		_port = port;
	if (_ip == "")
		_ip = addr;
#ifdef _WIN32
	int				iResult;

	iResult = WSAStartup(MAKEWORD(2, 2), &_wsaData);
	if (iResult != 0)
	{
		std::cerr << "WSAStartup failed: " << iResult << std::endl;
		return (false);
	}

	struct addrinfo	hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	_result = NULL;
	_ptr = NULL;

	iResult = getaddrinfo(_ip.c_str(), std::to_string(_port).c_str(), &hints, &_result);
	if (iResult != 0)
	{
		std::cerr << "getaddrinfo failed: " << iResult << std::endl;
		WSACleanup();
		return (false);
	}

	_connectSocket = INVALID_SOCKET;
	_ptr = _result;
	_connectSocket = socket(_ptr->ai_family, _ptr->ai_socktype, _ptr->ai_protocol);
	if (_connectSocket == INVALID_SOCKET)
	{
		std::cerr << "Error at socket(): " << WSAGetLastError() << std::endl;
		freeaddrinfo(_result);
		WSACleanup();
		return (false);
	}

	BOOL optVal = FALSE;
	_optLen = 1;

	iResult = setsockopt(_connectSocket, SOL_SOCKET, SO_KEEPALIVE, (char *)&optVal, _optLen);
	if (iResult == SOCKET_ERROR)
	{
		std::cerr << "setsockopt for SO_KEEPALIVE failed with error : " << WSAGetLastError() << std::endl;
		return (false);
	}

#elif __linux__
	if ((_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		std::cerr << "Could not create socket" << std::endl;
		return (false);
	}
	_server.sin_addr.s_addr = inet_addr(_ip.c_str());
	_server.sin_family = AF_INET;
	_server.sin_port = htons(_port);

	struct timeval timeout;      

	timeout.tv_sec = 10;
	timeout.tv_usec = 0;

	if (setsockopt (_sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
	  std::cerr << "setsockopt failed" << std::endl;

	if (setsockopt (_sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
	  std::cerr << "setsockopt failed" << std::endl;

#endif
	return (true);
}

bool				SocketClientTCP::sendData(const char *data)
{
#ifdef _WIN32
	const char		*sendbuf = data;
	int				iResult;
	short			datasize;
	char			len[2];

	len[0] = data[0];
	len[1] = data[1];
	datasize = *reinterpret_cast<short*>(len);
	iResult = send(_connectSocket, sendbuf, static_cast<int>(datasize), 0);
	if (iResult == SOCKET_ERROR)
	{
		std::cerr << "Send failed: " << WSAGetLastError() << std::endl;
		closesocket(_connectSocket);
		WSACleanup();
		_connected = false;
		return (false);
	}

	//iResult = shutdown(_connectSocket, SD_SEND);
	//if (iResult == SOCKET_ERROR)
	//{
	//	std::cerr << "Shutdown failed: " << WSAGetLastError() << std::endl;
	//	closesocket(_connectSocket);
	//	WSACleanup();
	//	return (false);
	//}

#elif __linux__
	if (send(_sock, data, datasize, 0) < 0)
	{
		std::cout << "Send failed" << std::endl;
		_connected = false;
		return (false);
	}

#endif
	return (true);
}

bool				SocketClientTCP::sendData(const char *data, const int datasize)
{
#ifdef _WIN32
	const char		*sendbuf = data;
	int				iResult;

	iResult = send(_connectSocket, sendbuf, static_cast<int>(datasize), 0);
	if (iResult == SOCKET_ERROR)
	{
		std::cerr << "Send failed: " << WSAGetLastError() << std::endl;
		closesocket(_connectSocket);
		WSACleanup();
		_connected = false;
		return (false);
	}

	//iResult = shutdown(_connectSocket, SD_SEND);
	//if (iResult == SOCKET_ERROR)
	//{
	//	std::cerr << "Shutdown failed: " << WSAGetLastError() << std::endl;
	//	closesocket(_connectSocket);
	//	WSACleanup();
	//	return (false);
	//}

#elif __linux__
	if (send(_sock, data, datasize, 0) < 0)
	{
		std::cout << "Send failed" << std::endl;
		_connected = false;
		return (false);
	}

#endif
	return (true);
}

char				*SocketClientTCP::receiveData()
{
	int			recvbuflen = TCP_BUFLEN;
	char			*recvbuf = new char[TCP_BUFLEN];

#ifdef _WIN32
	int				iResult;

	iResult = recv(_connectSocket, recvbuf, recvbuflen, 0);
	if (iResult > 0)
	{
		recvbuf[iResult - 1] = '\0';
		return (recvbuf);
	}
	return (NULL);

#elif __linux__
	int				ret;

	if ((ret = recv(_sock, recvbuf, recvbuflen, 0)) < 0)
	{
		return (NULL);
	}
	recvbuf[ret - 1] = '\0';
	return (recvbuf);
#endif
}

bool				SocketClientTCP::connectToServer()
{
#ifdef _WIN32
	int				iResult;

	iResult = connect(_connectSocket, _ptr->ai_addr, static_cast<int>(_ptr->ai_addrlen));
	if (iResult == SOCKET_ERROR)
	{
		closesocket(_connectSocket);
		_connectSocket = INVALID_SOCKET;
	}

	freeaddrinfo(_result);
	if (_connectSocket == INVALID_SOCKET)
	{
		std::cerr << "Unable to connect to server!" << std::endl;
		WSACleanup();
		return (false);
	}

#elif __linux__
	if (connect(_sock, reinterpret_cast<struct sockaddr *>(&_server), sizeof(_server)) < 0)
	{
		std::cerr << "Unable to connect to server!" << std::endl;
		return (false);
	}

#endif
	_connected = true;
	return (true);
}

bool			SocketClientTCP::closure()
{
#ifdef _WIN32
	int			iResult;

	_connected = false;
	iResult = shutdown(_connectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR)
	{
		std::cout << "Shutdown failed: " << WSAGetLastError();
		closesocket(_connectSocket);
		WSACleanup();
		return (false);
	}

#elif __linux__
	close(_sock);

#endif
	return (true);
}

void			SocketClientTCP::setOptLen(const int len)
{
	_optLen = len;
}

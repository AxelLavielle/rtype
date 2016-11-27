#include "SocketClientTCP.hh"

SocketClientTCP::SocketClientTCP()
{

}


SocketClientTCP::~SocketClientTCP()
{

}

bool				SocketClientTCP::init(const std::string &addr, int port)
{	
	int				iResult;

	iResult = WSAStartup(MAKEWORD(2, 2), &_wsaData);
	if (iResult != 0)
	{
		std::cerr << "WSAStartup failed: " << iResult << std::endl;
		return (false);
	}

	_result = NULL;
	_ptr = NULL;
	struct addrinfo	hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	iResult = getaddrinfo(addr.c_str(), std::to_string(port).c_str(), &hints, &_result);
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
		std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
		freeaddrinfo(_result);
		WSACleanup();
		return (false);
	}
}

bool				SocketClientTCP::sendData(const char *data)
{
	const char		*sendbuf = data;
	int				iResult;

	iResult = send(_connectSocket, sendbuf, (int)strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR)
	{
		std::cout << "send failed: " << WSAGetLastError() << std::endl;
		closesocket(_connectSocket);
		WSACleanup();
		return (bool);
	}

	printf("Bytes Sent: %ld\n", iResult);

	iResult = shutdown(_connectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR)
	{
		std::cout << "shutdown failed: " << WSAGetLastError() << std::endl;
		closesocket(_connectSocket);
		WSACleanup();
		return (bool);
	}
}

char				*SocketClientTCP::receiveData()
{
	int				recvbuflen = DEFAULT_BUFLEN;
	char			recvbuf[DEFAULT_BUFLEN];
	int				iResult;

	iResult = recv(_connectSocket, recvbuf, recvbuflen, 0);
	while (iResult > 0)
	{
		iResult = recv(_connectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
			std::cout << "Bytes received: " << iResult << std::endl;
		else if (iResult == 0)
			std::cout << "Connection closed" << std::endl;
		else
			std::cout << "recv failed: " << WSAGetLastError() << std::endl;
	}
}

bool				SocketClientTCP::connectToServer()
{
	int				iResult;

	iResult = connect(_connectSocket, _ptr->ai_addr, (int)_ptr->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		closesocket(_connectSocket);
		_connectSocket = INVALID_SOCKET;
	}

	freeaddrinfo(_result);
	if (_connectSocket == INVALID_SOCKET)
	{
		std::cout << "Unable to connect to server!" << std::endl;
		WSACleanup();
		return (false);
	}
}
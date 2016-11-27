#include "SocketServerTCP.hh"



SocketServerTCP::SocketServerTCP()
{
	_socketServerID = INVALID_SOCKET;
}


SocketServerTCP::~SocketServerTCP()
{
}

bool SocketServerTCP::init(const std::string &addr, int port)
{
	WSADATA			wsaData;
	struct addrinfo hints;
	
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) 
	{
		OutputDebugString("WSAStartup failed\n");
		return (false);
	}

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
	
	if (getaddrinfo(NULL, std::to_string(port).c_str(), &hints, &_addrSocket) != 0)
	{
		OutputDebugString("Getaddrinfo failed\n");
		WSACleanup();
		return (false);
	}

	if ((_socketServerID = socket(_addrSocket->ai_family, _addrSocket->ai_socktype, _addrSocket->ai_protocol)) == INVALID_SOCKET)
	{
		OutputDebugString("Socket creation : ");
		OutputDebugString(std::to_string(WSAGetLastError()).c_str());
		freeaddrinfo(_addrSocket);
		WSACleanup();
		return (false);
	}
	return (true);
}

bool SocketServerTCP::launch()
{
	if (bind(_socketServerID, _addrSocket->ai_addr, _addrSocket->ai_addrlen) == SOCKET_ERROR)
	{
		OutputDebugString("Bind failed\n");
		freeaddrinfo(_addrSocket);
		closesocket(_socketServerID);
		WSACleanup();
		return (false);
	}
	freeaddrinfo(_addrSocket);

	if (listen(_socketServerID, SOMAXCONN) == INVALID_SOCKET)
	{
		OutputDebugString("Listen failed\n");
		closesocket(_socketServerID);
		WSACleanup();
		return (false);
	}
	return (true);
}

int SocketServerTCP::acceptNewClient()
{
	int newClientSocketID;

	if ((newClientSocketID = accept(_socketServerID, NULL, NULL)) == INVALID_SOCKET)
	{
		OutputDebugString("Accept failed\n");
		closesocket(_socketServerID);
		WSACleanup();
		return (-1);
	}

	OutputDebugString("NEW CLIENT ------->");
	OutputDebugString(std::to_string(newClientSocketID).c_str());
	OutputDebugString("\n");

	return (newClientSocketID);
}

bool SocketServerTCP::sendData(const char * data)
{
	return false;
}

char *SocketServerTCP::receiveData()
{
	return (NULL);
}


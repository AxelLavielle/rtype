#include "SocketClientUDP.hh"

SocketClientUDP::SocketClientUDP()
{
}

SocketClientUDP::~SocketClientUDP()
{
}

bool			SocketClientUDP::init(const std::string &addr, int port)
{
#ifdef _WIN32
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		std::cerr << "Failed. Error Code : " << WSAGetLastError() << std::endl;
		return (false);
	}

	if ((_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		std::cerr << "socket() failed with error code : " << WSAGetLastError() << std::endl;
		return (false);
	}

	memset((char *)&_siOther, 0, sizeof(_siOther));
	_siOther.sin_family = AF_INET;
	_siOther.sin_port = htons(port);
	inet_pton(AF_INET, addr.c_str(), &_siOther.sin_addr.S_un.S_addr);

	sendto(_sock, "", 1, 0, (struct sockaddr *)&_siOther, sizeof(_siOther));

#elif __linux__
	if ((_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		std::cout << "Error when creating socket" << std::endl;
		return (false);
	}

	memset((char *)&_siMe, 0, sizeof(_siMe));
	_siMe.sin_family = AF_INET;
	_siMe.sin_port = htons(port);
	_siMe.sin_addr.s_addr = htonl(addr.c_str());

#endif
	return (true);
}

bool			SocketClientUDP::sendData(const char *data)
{
	int			slen = sizeof(_siOther);

#ifdef _WIN32
	if (sendto(_sock, data, strlen(data), 0, (struct sockaddr *)&_siOther, slen) == SOCKET_ERROR)
	{
		std::cerr << "sendto() failed with error code : " << WSAGetLastError() << std::endl;
		return (false);
	}
#elif __linux__
	if (sendto(_sock, data, strlen(data), 0, (struct sockaddr*)&_siOther, slen) == -1)
	{
		std::cerr << "Send failed" << std::endl;
		return (false);
	}
#endif
	return (true);
}

char			*SocketClientUDP::receiveData()
{
	char		*buf = new char[UDP_BUFLEN];
	int			slen = sizeof(_siOther);

#ifdef _WIN32
	memset(buf, '\0', UDP_BUFLEN);
	if (recvfrom(_sock, buf, UDP_BUFLEN, 0, (struct sockaddr *)&_siOther, &slen) == SOCKET_ERROR)
	{
		std::cerr << "recvfrom() failed with error code : " << WSAGetLastError() << std::endl;
		return (NULL);
	}

#elif __linux__
	if (recvfrom(_sock, buf, UDP_BUFLEN, 0, (struct sockaddr *)&_siOther, &slen) == -1)
	{
		std::cerr << "Receive failed" << std::endl;
		return (NULL);
	}

#endif
	return (buf);
}

bool			SocketClientUDP::close()
{
#ifdef _WIN32
	closesocket(_sock);
	WSACleanup();

#elif __linux__
	close(_sock);

#endif
	return (true);
}

bool			SocketClientUDP::connectToServer()
{
#ifdef __linux__
	if (bind(_sock, (struct sockaddr*)&_siMe, sizeof(_siMe)) == -1)
	{
		std::cout << "Error in bind" << std::endl;
		return (false);
	}
#endif
	return (true);
}
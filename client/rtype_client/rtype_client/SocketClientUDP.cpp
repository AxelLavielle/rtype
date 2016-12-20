#include "SocketClientUDP.hh"

SocketClientUDP::SocketClientUDP()
{
}

SocketClientUDP::~SocketClientUDP()
{
}

bool			SocketClientUDP::init(const std::string &addr, const int port)
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

	memset(reinterpret_cast<char *>(&_siOther), 0, sizeof(_siOther));
	_siOther.sin_family = AF_INET;
	_siOther.sin_port = htons(port);
	inet_pton(AF_INET, addr.c_str(), &_siOther.sin_addr.S_un.S_addr);

	//sendto(_sock, "", 1, 0, reinterpret_cast<struct sockaddr *>(&_siOther), sizeof(_siOther));

#elif __linux__
	if ((_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		std::cout << "Error when creating socket" << std::endl;
		return (false);
	}

	memset(reinterpret_cast<char *>(&_siOther), 0, sizeof(_siOther));
	_siOther.sin_family = AF_INET;
	_siOther.sin_port = htons(port);
	if (inet_aton(addr.c_str() , &_siOther.sin_addr) == 0)
	  {
	    perror("inet_aton");
	    return (false);
	  }

	//sendto(_sock, "", 1, 0, reinterpret_cast<struct sockaddr *>(&_siOther), sizeof(_siOther));

#endif
	return (true);
}

bool			SocketClientUDP::sendData(const char *data, const int datasize)
{
	int			slen = sizeof(_siOther);

#ifdef _WIN32
	int			res;

	if ((res = sendto(_sock, data, datasize, 0, reinterpret_cast<struct sockaddr *>(&_siOther), slen)) == SOCKET_ERROR)
	{
		std::cerr << "sendto() failed with error code : " << WSAGetLastError() << std::endl;
		return (false);
	}
#elif __linux__
	if (sendto(_sock, data, datasize, 0, reinterpret_cast<struct sockaddr *>(&_siOther), slen) == -1)
	{
		perror("sendto");
		return (false);
	}
#endif
	return (true);
}

char			*SocketClientUDP::receiveData()
{
	char		*buf = new char[UDP_BUFLEN];
	int		slen = sizeof(_siOther);

#ifdef _WIN32
	memset(buf, '\0', UDP_BUFLEN);
	if (recvfrom(_sock, buf, UDP_BUFLEN, 0, reinterpret_cast<struct sockaddr *>(&_siOther), &slen) == SOCKET_ERROR)
	{
		return (NULL);
	}

#elif __linux__
	memset(buf, '\0', UDP_BUFLEN);
	if (recvfrom(_sock, buf, UDP_BUFLEN, 0, reinterpret_cast<struct sockaddr *>(&_siOther), reinterpret_cast<socklen_t *>(&slen)) == -1)
	{
		return (NULL);
	}
#endif
	return (buf);
}

bool			SocketClientUDP::closure()
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
	return (true);
}

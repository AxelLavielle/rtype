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
#endif

	if ((_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		std::cerr << "socket() failed with error code : " << std::endl;
		//std::cerr << "socket() failed with error code : " << WSAGetLastError() << std::endl;
		return (false);
	}

	memset(reinterpret_cast<char *>(&_siOther), 0, sizeof(_siOther));
	_siOther.sin_family = AF_INET;
	_siOther.sin_port = htons(port);
	_siOther.sin_addr.s_addr = htonl(INADDR_ANY);
//	inet_pton(AF_INET, addr.c_str(), &_siOther.sin_addr.S_un.S_addr);

	if (bind(_sock, reinterpret_cast<struct sockaddr *>(&_siOther), sizeof(_siOther)) == -1)
	{
		std::cerr << "bind() failed with error code : " << std::endl;
		// std::cerr << "bind() failed with error code : " << WSAGetLastError() << std::endl;
	}

	_connected = true;
	return (true);
}

bool			SocketClientUDP::sendData(const char *data)
{
	int				slen = sizeof(_siOther);
	short			datasize;
	char			len[2];

	len[0] = data[0];
	len[1] = data[1];
	datasize = *reinterpret_cast<short*>(len);

	if (sendto(_sock, data, datasize, 0, reinterpret_cast<struct sockaddr *>(&_siOther), slen) == SOCKET_ERROR)
	{
#ifdef _WIN32
	  std::cerr << "sendto() failed with error code : " << WSAGetLastError() << std::endl;

#elif __linux__

	  perror("sendto");

#endif
	  _connected = false;
	  return (false);
	}
	return (true);
}

bool			SocketClientUDP::sendData(const char *data, const int datasize)
{
	int			slen = sizeof(_siOther);

	int			res;

	if ((res = sendto(_sock, data, datasize, 0, reinterpret_cast<struct sockaddr *>(&_siOther), slen)) == SOCKET_ERROR)
	{
	  #ifdef _WIN32
		std::cerr << "sendto() failed with error code : " << WSAGetLastError() << std::endl;
	  #elif __linux__
		perror("sendto: ");
	  #endif
		_connected = false;
		return (false);
	}
	return (true);
}

char			*SocketClientUDP::receiveData()
{
	char		*buf = new char[TCP_PACKET_SIZE];
	int			slen = sizeof(struct sockaddr);

	int			ret;
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 1000;

	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(_sock, &readfds);

	ret = select(_sock + 1, &readfds, NULL, NULL, &tv);
	if (ret > 0)
	{
		if (FD_ISSET(_sock, &readfds))
		{
			memset(buf, '\0', TCP_PACKET_SIZE);
			if ((ret = recvfrom(_sock, buf, TCP_PACKET_SIZE, 0, reinterpret_cast<struct sockaddr *>(&_siOther), reinterpret_cast<socklen_t *>(&slen))) == SOCKET_ERROR)
			{
#ifdef _WIN32
				std::cout << "recvfrom failed with the error : " << WSAGetLastError() << std::endl;

#elif __linux__

				perror("recvfrom");

#endif
				return (NULL);
			}
		}
		std::cout << "LEN RECV == " << ret << std::endl;
	}
	else if (ret == 0)
	  {
		std::cout << "timed out waiting for ack" << std::endl;
		return (NULL);
	  }
	else
	  {
		std::cerr << "error selecting" << std::endl;
		return (NULL);
	  }

	return (buf);
}

bool			SocketClientUDP::closure()
{
	_connected = false;
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

#include "SocketServerUDP.hh"

SocketServerUDP::SocketServerUDP() : ASocketServer()
{
	_fdMax = 0;
	_socketServerID = INVALID_SOCKET;
}

SocketServerUDP::~SocketServerUDP()
{
}

void	SocketServerUDP::displayError(const std::string &msg)
{
	#ifdef __linux__
		perror(msg.c_str());
	#elif _WIN32
		std::cerr << msg << WSAGetLastError() << std::endl;
	#endif
}

bool SocketServerUDP::init(const std::string &addr, int port)
{
	#ifdef _WIN32
		WSADATA			wsaData;

		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		{
			std::cerr << "WSAStartup failed" << std::endl;
			return (false);
		}
	#endif

	MemTools::set(&_addrSocket, 0, sizeof(struct sockaddr_in));
	_addrSocket.sin_addr.s_addr = htonl(INADDR_ANY);
	_addrSocket.sin_family = AF_INET;
	_addrSocket.sin_port = htons(port);

	if ((_socketServerID = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		displayError("Socket creation failed: ");
		#ifdef _WIN32
			WSACleanup();
		#endif
		return (false);
	}
	_fdMax = _socketServerID;
	(void)addr;
	return (true);
}

bool SocketServerUDP::launch()
{
	if (bind(_socketServerID, reinterpret_cast<struct sockaddr *>(&_addrSocket), sizeof(struct sockaddr_in)) == SOCKET_ERROR)
	{
		displayError("Bind failed: ");
		#ifdef _WIN32
			WSACleanup();
			closesocket(_socketServerID);
		#elif __linux__
			close(_socketServerID);
		#endif
		return (false);
	}
	return (true);
}

int						SocketServerUDP::acceptNewClient(struct sockaddr_in *clientAddr)
{
	//int					newSocketClient;
	char				buffer[UDP_PACKET_SIZE];
	socklen_t			addrSize;
	int					ret;

	addrSize = static_cast<socklen_t>(sizeof(struct sockaddr_in));
	MemTools::set(&clientAddr, 0, sizeof(struct sockaddr));
	
	if ((ret = recvfrom(_socketServerID, buffer, sizeof(buffer) - 1,
						0, reinterpret_cast<struct sockaddr *>(&clientAddr), &addrSize)) < 0)
	{
		displayError("Recvfrom failed: ");
		return (-1);
	}
	buffer[ret] = '\0';

	std::cout << "HEY HEY HEY : " << buffer << std::endl;

	return (ret);
}

bool										SocketServerUDP::sendAllData(std::vector<ServerClient *> &clientList)
{
	std::vector<ServerClient *>::iterator	it;

	it = clientList.begin();
	while (it != clientList.end())
	{
		if ((*it)->getDataLenUDP() > 0)
		{
			if (DEBUG_MSG)
				std::cout << "Sending to Client " << (*it)->getUDPSocket()
					<< " : " << (*it)->getSendDataUDP() << std::endl;


			if (sendto((*it)->getUDPSocket(), (*it)->getSendDataUDP(), (*it)->getDataLenUDP(),
				0, reinterpret_cast<struct sockaddr *>((*it)->getAddrUDP()), sizeof(struct sockaddr *)) < 0)
			{
				displayError("Sendto failed: ");
			}

			(*it)->resetDataUDP();
		}
		it++;
	}
	return (true);
}

std::string	serialize(const char *str, int len)
{
	(void)len;
	return (std::string(str));
}

std::vector<ClientMsg>		SocketServerUDP::receiveData(std::vector<ServerClient *> &socketsClients)
{
	std::vector<ServerClient *>::iterator	it;
	char									buf[UDP_PACKET_SIZE];
	std::vector<ClientMsg>					vectMsg;
	int										len;
	int										addrSize;

	it = socketsClients.begin();
	while (it != socketsClients.end())
	{
		if (FD_ISSET((*it)->getUDPSocket(), &_readfds))
		{
			MemTools::set(buf, 0, UDP_PACKET_SIZE);
			if ((len = recvfrom((*it)->getUDPSocket(), buf, sizeof(buf) - 1,
					    0, reinterpret_cast<struct sockaddr *>((*it)->getAddrUDP()), reinterpret_cast<socklen_t *>(&addrSize))) <= 0)
			{
				if (len == -1)
				{
					displayError("Recvfrom error: ");
				}
				#ifdef _WIN32
					closesocket((*it)->getUDPSocket());
				#elif	__linux__
					close((*it)->getUDPSocket());
				#endif
					(*it)->setDisconnectedUDP(true);
			}
			else
			{
				buf[len] = '\0';
				if (DEBUG_MSG)
					std::cout << "Received Msg [" << buf << "]" << std::endl;
				vectMsg.push_back(std::make_pair((*it), serialize(buf, len)));
			}





		}
		it++;
	}
	return (vectMsg);
}

int										SocketServerUDP::selectFds(const std::vector<int> &socketsClients)
{
	std::vector<int>::const_iterator	it;

	FD_ZERO(&_readfds);
	FD_ZERO(&_writefds);
	FD_SET(_socketServerID, &_readfds);
	_fdMax = _socketServerID;

	it = socketsClients.begin();
	while (it != socketsClients.end())
	{
		FD_SET(*it, &_readfds);
		FD_SET(*it, &_writefds);
		if ((*it) > _fdMax)
			_fdMax = (*it);
		it++;
	}

	if (select(_fdMax + 1, &_readfds, &_writefds, NULL, NULL) < 0)
	{
		displayError("Select error: ");
	}

	return (0);
}

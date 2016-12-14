#include "SocketServerTCP.hh"

SocketServerTCP::SocketServerTCP() : ASocketServer()
{
	_fdMax = 0;
	_socketServerID = INVALID_SOCKET;
}

SocketServerTCP::~SocketServerTCP()
{
}

void	SocketServerTCP::displayError(const std::string &msg)
{
	#ifdef __linux__
		perror(msg.c_str());
	#elif _WIN32
		std::cerr << msg << WSAGetLastError() << std::endl;
	#endif
}

bool SocketServerTCP::init(const std::string &addr, int port)
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

	if ((_socketServerID = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
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

bool SocketServerTCP::launch()
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

	if (listen(_socketServerID, SOMAXCONN) == INVALID_SOCKET)
	{
		displayError("Listen failed: ");
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

int SocketServerTCP::acceptNewClient()
{
	int newClientSocketID;

	if (!FD_ISSET(_socketServerID, &_readfds))
		return (-1);

	if ((newClientSocketID = accept(_socketServerID, NULL, NULL)) == INVALID_SOCKET)
	{
		displayError("Accept failed: ");
		#ifdef _WIN32
			WSACleanup();
			closesocket(_socketServerID);
		#elif __linux__
			close(_socketServerID);
		#endif
		return (-1);
	}

	if (DEBUG_MSG)
		std::cout << "NEW CLIENT ------->" << newClientSocketID << std::endl;

	return (newClientSocketID);
}

bool										SocketServerTCP::sendAllData(std::vector<ServerClient *> &clientList)
{
	std::vector<ServerClient *>::iterator	it;

	it = clientList.begin();
	while (it != clientList.end())
	{
		if ((*it)->getDataLen() > 0)
		{
			if (DEBUG_MSG)
				std::cout << "Sending to Client " << (*it)->getTCPSocket()
					<< " : " << (*it)->getSendData() << std::endl;
			if (send((*it)->getTCPSocket(), (*it)->getSendData(), (*it)->getDataLen(), 0) == SOCKET_ERROR)
			{
				displayError("Send error");
			}
			(*it)->resetData();
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

std::vector<ClientMsg>		SocketServerTCP::receiveData(std::vector<ServerClient *> &socketsClients)
{
	std::vector<ServerClient *>::iterator	it;
	char									buf[TCP_PACKET_SIZE];
	std::vector<ClientMsg>					vectMsg;
	int										len;

	it = socketsClients.begin();
	while (it != socketsClients.end())
	{
		if (FD_ISSET((*it)->getTCPSocket(), &_readfds))
		{
			MemTools::set(buf, 0, TCP_PACKET_SIZE);
			if ((len = recv((*it)->getTCPSocket(), buf, TCP_PACKET_SIZE, 0)) == -1 || len == 0)
			{
				if (len == -1)
				{
					displayError("Recv error: ");
				}
				#ifdef _WIN32
					closesocket((*it)->getTCPSocket());
				#elif	__linux__
					close((*it)->getTCPSocket());
				#endif
				(*it)->setDisconnected(true);
			}
			else
			{
				if (DEBUG_MSG)
					std::cout << "Received Msg [" << buf << "]" << std::endl;
				vectMsg.push_back(std::make_pair((*it), serialize(buf, len)));
			}
		}
		it++;
	}
	return (vectMsg);
}

int										SocketServerTCP::selectFds(const std::vector<int> &socketsClients)
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

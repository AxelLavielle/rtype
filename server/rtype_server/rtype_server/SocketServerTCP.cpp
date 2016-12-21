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

bool					SocketServerTCP::init(const std::string &addr, const int port)
{
	#ifdef _WIN32
		WSADATA			wsaData;

		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		{
			std::cerr << "WSAStartup failed" << std::endl;
			return (false);
		}
	#endif

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
	_port = port;
	return (true);
}

bool SocketServerTCP::launch()
{
	MemTools::set(&_addrSocket, 0, sizeof(struct sockaddr_in));
	_addrSocket.sin_addr.s_addr = htonl(INADDR_ANY);
	_addrSocket.sin_family = AF_INET;
	_addrSocket.sin_port = htons(_port);

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
		if ((*it)->getDataLenTCP() > 0)
		{
			if (DEBUG_MSG)
				std::cout << "Sending to Client " << (*it)->getTCPSocket()
					<< " : " << (*it)->getSendDataTCP() << std::endl;
			if (send((*it)->getTCPSocket(), (*it)->getSendDataTCP(), (*it)->getDataLenTCP(), 0) == SOCKET_ERROR)
			{
				displayError("Send error");
			}
			(*it)->resetDataTCP();
		}
		it++;
	}
	return (true);
}

std::string	serialize2(const char *str, int len)
{
	(void)len;
	return (std::string(str));
}

std::vector<ClientMsg>						SocketServerTCP::receiveData(std::vector<ServerClient *> &socketsClients)
{
	std::vector<ServerClient *>::iterator	it;
	char									buf[TCP_PACKET_SIZE];
	std::vector<ClientMsg>					vectMsg;
	int										len;
	Serialize								serializer;

	it = socketsClients.begin();
	while (it != socketsClients.end())
	{
		if (FD_ISSET((*it)->getTCPSocket(), &_readfds))
		{
			MemTools::set(buf, 0, TCP_PACKET_SIZE);
			if ((len = recv((*it)->getTCPSocket(), buf, TCP_PACKET_SIZE, 0)) == -1)
			{
				displayError("Recv error: ");
				
				#ifdef  _WIN32
					closesocket((*it)->getTCPSocket());
				#elif	__linux__
					close((*it)->getTCPSocket());
				#endif
				std::cout << "Disconnection : RECEIVE : LEN = " << len << std::endl;
				(*it)->setDisconnectedTCP(true);
			}
			else if (len > 0)
			{
				if (DEBUG_MSG)
					std::cout << "\\\\ Received Msg of len [" << len << "]" << std::endl;
				vectMsg.push_back(std::make_pair((*it), Serialize::unserializeCommand(buf)));
			}
		}
		it++;
	}
	return (vectMsg);
}

int										SocketServerTCP::selectFds(const std::vector<int> &socketsClients)
{
	std::vector<int>::const_iterator	it;
	struct timeval						tv;

	tv.tv_sec = 0;
	tv.tv_usec = 100000;

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

	if (select(_fdMax + 1, &_readfds, &_writefds, NULL, &tv) < 0)
	{
		displayError("Select error: ");
	}

	return (0);
}

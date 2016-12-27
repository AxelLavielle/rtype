#include "SocketServerUDP.hh"

SocketServerUDP::SocketServerUDP() : ASocketServer()
{}

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

bool SocketServerUDP::init(const std::string &addr, const int port)
{
	#ifdef _WIN32
		WSADATA			wsaData;
	    

		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		{
			std::cerr << "WSAStartup failed" << std::endl;
			return (false);
		}
	#endif

		addr.c_str();
	if ((_socketServerID = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		displayError("Socket UDP Creation failed: ");
		return (false);
	}
	_port = port;
	return (true);
}

bool					SocketServerUDP::launch()
{
	MemTools::set(&_addrSocket, 0, sizeof(_addrSocket));
	_addrSocket.sin_family = AF_INET;
	_addrSocket.sin_port = htons(_port);
	_addrSocket.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(_socketServerID, (struct sockaddr *)&_addrSocket, sizeof(_addrSocket)) == SOCKET_ERROR)
	{
		displayError("Socket UDP Bind failed: ");
		return (false);
	}

	return (true);
}

bool										SocketServerUDP::sendAllData(std::vector<ServerClient *> &clientList)
{
	std::vector<ServerClient *>::iterator	it;
	int										len;

	if (FD_ISSET(_socketServerID, &_writefds) == false)
		return (false);
	it = clientList.begin();
	while (it != clientList.end())
	{
		if ((*it)->getDataLenUDP() > 0)
		{
			struct sockaddr_in newAddr;

			MemTools::copy(&newAddr, &_addrSocket, sizeof(_addrSocket));
			newAddr.sin_addr = (*it)->getAddr().getAddr();
			len = sendto(_socketServerID, (*it)->getSendDataUDP(), (*it)->getDataLenUDP(),
						0, (struct sockaddr *)&newAddr, sizeof(struct sockaddr));
			if (len == -1)
			{
				std::cout << "ERROR " << WSAGetLastError() << std::endl;
				//displayError("Sendto failed: ");
			}
			//std::cout << "UDP Sent " << len << " characters" << std::endl;
		}
		(*it)->resetDataUDP();
		it++;
	}
	return (true);
}

std::vector<ICommand *>		SocketServerUDP::receiveData()
{
	std::vector<ICommand *>		vectMsg;
	char						buf[UDP_PACKET_SIZE];
	int							len;
	struct sockaddr_in			clientAddr;
	int							clientAddrSize;

	if (FD_ISSET(_socketServerID, &_readfds) == false)
		return (vectMsg);
	std::cout << "Receiving data UDP" << std::endl;
	clientAddrSize = sizeof(clientAddr);
	MemTools::set(buf, 0, UDP_PACKET_SIZE);
	len = recvfrom(_socketServerID, buf, UDP_PACKET_SIZE, 0, (struct sockaddr *)&clientAddr, (socklen_t *)&clientAddrSize);
	if (len == -1)
	{
		displayError("Recvfrom failed: ");
	}
	else
	{
		//std::cout << "Received new Msg of " << len << " characters" << std::endl;

		vectMsg.push_back(Serialize::unserializeCommand(buf));
	}
	return (vectMsg);
}

int										SocketServerUDP::selectFds()
{
	std::vector<int>::const_iterator	it;
	int									fdMax;
	struct timeval						tv;

	tv.tv_sec = 0;
	tv.tv_usec = 100000;
	if (setsockopt(_socketServerID, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv)) < 0)
	{
		perror("Error");
	}

	FD_ZERO(&_readfds);
	FD_ZERO(&_writefds);
	FD_SET(_socketServerID, &_readfds);
	FD_SET(_socketServerID, &_writefds);
	fdMax = _socketServerID;

	if (select(fdMax + 1, &_readfds, &_writefds, NULL, &tv) < 0)
	{
		displayError("Select error: ");
	}
	return (0);
}

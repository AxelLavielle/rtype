#include "SocketServerUDP.hh"

SocketServerUDP::SocketServerUDP() : ASocketServer()
{}

SocketServerUDP::~SocketServerUDP()
{
}

void	SocketServerUDP::displayError(const std::string &msg)
{
#ifdef _WIN32
  std::cerr << msg << WSAGetLastError() << std::endl;
#elif __linux__
  perror(msg.c_str());
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
	std::cout << "UDP Port -> [" << _port << "]" << std::endl;
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
	std::vector<char *>::iterator			itMsg;
	int										len;

	if (FD_ISSET(_socketServerID, &_writefds) == false)
		return (false);
	it = clientList.begin();
	while (it != clientList.end())
	{
		struct sockaddr_in newAddr;

		MemTools::copy(&newAddr, &_addrSocket, sizeof(_addrSocket));
		newAddr.sin_addr = (*it)->getAddr().getAddr();

		std::vector<char *>			udpDatas;
		udpDatas = (*it)->getUDPDatas();
		itMsg = udpDatas.begin();
		
		while (itMsg != udpDatas.end())
		{
			char	dataLen[2];
			short	dataSize;

			dataLen[0] = (*itMsg)[0];
			dataLen[1] = (*itMsg)[1];
			dataSize = *reinterpret_cast<short*>(dataLen);
			len = sendto(_socketServerID, (*itMsg), dataSize, 0, (struct sockaddr *)&newAddr, sizeof(struct sockaddr));
			if (len == -1)
			{
				#ifdef _WIN32
					std::cout << "Sendto failed " << WSAGetLastError() << std::endl;
				#elif __linux__
					displayError("Sendto failed: ");
				#endif
			}
			//std::cout << "UDP Sent " << len << " characters to client [" << (*it)->getTCPSocket() << "]" << std::endl;
			itMsg++;
		}
		(*it)->resetDataUDP();
		
		it++;
	}
	return (true);
}

std::vector<ICommand *>		SocketServerUDP::receiveData()
{
	std::vector<ICommand *>		vectMsg;
	char						buf[TCP_PACKET_SIZE];
	int							len;
	struct sockaddr_in			clientAddr;
	int							clientAddrSize;

	if (FD_ISSET(_socketServerID, &_readfds) == false)
		return (vectMsg);
	//std::cout << "Receiving data UDP" << std::endl;

	clientAddrSize = sizeof(clientAddr);
	MemTools::set(buf, 0, TCP_PACKET_SIZE);
	len = recvfrom(_socketServerID, buf, TCP_PACKET_SIZE, 0, (struct sockaddr *)&clientAddr, (socklen_t *)&clientAddrSize);
	if (len == -1)
	{
		// std::cout << "Recvfrom failed : " << WSAGetLastError() << std::endl;
		//displayError("Recvfrom failed: ");
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
	tv.tv_usec = 1000;
	if (setsockopt(_socketServerID, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv)) < 0)
	{
		perror("Error");
	}

	FD_ZERO(&_readfds);
	FD_ZERO(&_writefds);
	FD_SET(_socketServerID, &_readfds);
	FD_SET(_socketServerID, &_writefds);
	fdMax = _socketServerID;

	int ret;
	if ((ret = select(fdMax + 1, &_readfds, NULL, NULL, &tv)) <= 0)
	{
		if (ret == -1)
			displayError("Select error: ");
		return (-1);
	}

	return (0);
}

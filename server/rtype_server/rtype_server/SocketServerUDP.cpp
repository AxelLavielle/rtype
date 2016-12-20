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
	struct sockaddr_in	serverAddr;

	MemTools::set(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(_port);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(_socketServerID, (SOCKADDR *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		displayError("Sokcet UDP Bind failed: ");
		return (false);
	}

	return (true);
}

bool										SocketServerUDP::sendAllData(std::vector<ServerClient *> &clientList)
{
	std::vector<ServerClient *>::iterator	it;
	int										len;

	it = clientList.begin();
	while (it != clientList.end())
	{
		len = sendto(_socketServerID, (*it)->getSendDataUDP(), (*it)->getDataLenUDP(),
						0, (SOCKADDR *)(*it)->getAddrUDP(), sizeof(struct sockaddr_in));
		if (len == -1)
		{
			displayError("Sendto failed: ");
		}
		it++;
	}
	return (true);
}

std::vector<UDPClientMsg>		SocketServerUDP::receiveData()
{
	std::vector<UDPClientMsg>	vectMsg;
	char						buf[UDP_PACKET_SIZE];
	int							len;
	struct sockaddr_in			clientAddr;
	int							clientAddrSize;

	clientAddrSize = sizeof(clientAddr);
	MemTools::set(buf, 0, UDP_PACKET_SIZE);
	len = recvfrom(_socketServerID, buf, UDP_PACKET_SIZE, 0, (struct sockaddr *)&clientAddr, &clientAddrSize);
	if (len == -1)
	{
		displayError("Recvfrom failed: ");
	}
	else
	{
		std::cout << "Add new Msg of " << len << " characters" << std::endl;
		vectMsg.push_back(std::make_pair(&clientAddr, Serialize::unserializeCommand(buf)));
	}
	return (vectMsg);
}
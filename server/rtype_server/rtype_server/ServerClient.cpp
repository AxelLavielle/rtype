#include "ServerClient.hh"

ServerClient::ServerClient(const int socketFd, SocketAddress *addr)
{
	_TCPSocketFd = socketFd;
	MemTools::set(_sendDataTCP, 0, TCP_PACKET_SIZE);
	_lenDataTCP = 0;
	_isDisconnectedTCP = false;

	MemTools::set(_sendDataUDP, 0, TCP_PACKET_SIZE);
	_lenDataUDP = 0;
	_clientAddr = addr;
	
	_readyStatus = false;
	_logState = false;
	_currentRoomId = -1;
	_playerName = "";
}

ServerClient::~ServerClient()
{
}

int			ServerClient::getTCPSocket() const
{
	return (_TCPSocketFd);
}

void		ServerClient::addTCPDataToSend(const char *data)
{
	/*int		i;
	int		j;
	short	size;
	char	len[2];

	i = _lenDataTCP;
	j = 0;
	len[0] = data[0];
	len[1] = data[1];
	size = *reinterpret_cast<short*>(len);
	while (j < size && i < TCP_PACKET_SIZE)
	{
		_sendDataTCP[i] = data[j];
		i++;
		j++;
	}
	_lenDataTCP += size;*/

	char	dataLen[2];
	short	dataSize;

	dataLen[0] = data[0];
	dataLen[1] = data[1];
	dataSize = *reinterpret_cast<short*>(dataLen);

	char *dataCpy = new char[dataSize];
	int i;
	i = 0;
	while (i < dataSize && i < TCP_PACKET_SIZE)
	{
		dataCpy[i] = data[i];
		i++;
	}
	_tcpDatas.push_back(dataCpy);
}

const char	*ServerClient::getSendDataTCP() const
{
	return (&(_sendDataTCP[0]));
}

void		ServerClient::resetDataTCP()
{
	_tcpDatas.clear();
}

int			ServerClient::getDataLenTCP() const
{
	return (_lenDataTCP);
}

bool ServerClient::isDisconnectedTCP() const
{
	return (_isDisconnectedTCP);
}

void	ServerClient::setDisconnectedTCP(const bool disconnected)
{
	_isDisconnectedTCP = disconnected;
}

SocketAddress	ServerClient::getAddr() const
{
	return (*_clientAddr);
}

void		ServerClient::addUDPDataToSend(const char *data)
{
	char	dataLen[2];
	short	dataSize;

	dataLen[0] = data[0];
	dataLen[1] = data[1];
	dataSize = *reinterpret_cast<short*>(dataLen);

	char *dataCpy = new char[dataSize];
	int i;
	i = 0;
	while (i < dataSize && i < TCP_PACKET_SIZE)
	{
		dataCpy[i] = data[i];
		i++;
	}

	_udpDatas.push_back(dataCpy);
}

const char *ServerClient::getSendDataUDP() const
{
	return (&(_sendDataUDP[0]));
}

std::vector<char *> ServerClient::getUDPDatas() const
{
	return (_udpDatas);
}

std::vector<char*> ServerClient::getTCPDatas() const
{
	return (_tcpDatas);
}

void ServerClient::resetDataUDP()
{
	//MemTools::set(_sendDataUDP, 0, TCP_PACKET_SIZE);
	//_lenDataUDP = 0;
	_udpDatas.clear();
}

int ServerClient::getDataLenUDP() const
{
	return (_lenDataUDP);
}

void	ServerClient::setCurrentRoom(const int roomId)
{
	_currentRoomId = roomId;
}

int		ServerClient::getCurrentRoom() const
{
	return (_currentRoomId);
}

void	ServerClient::setLogged(const bool state)
{
	_logState = state;
}

bool	ServerClient::isLogged() const
{
	return (_logState);
}

void ServerClient::setPlayerName(const std::string &name)
{
	_playerName = name;
}

std::string ServerClient::getPlayerName() const
{
	return (_playerName);
}

void ServerClient::setStatus(const bool status)
{
	_readyStatus = status;
}

bool ServerClient::isReady() const
{
	return (_readyStatus);
}

void ServerClient::addInput(const InputCmd &newInput)
{
	_inputs.push_back(newInput);
}

std::vector<InputCmd>	ServerClient::getInputs() const
{
	return (_inputs);
}

void ServerClient::clearInput()
{
	_inputs.clear();
}

void ServerClient::setPlayer(IEntity * player)
{
	_player = player;
}

IEntity * ServerClient::getPlayer() const
{
	return (_player);
}

#include "ServerClient.hh"

ServerClient::ServerClient(const int socketFd)
{
	_TCPSocketFd = socketFd;
	MemTools::set(_sendDataTCP, 0, TCP_PACKET_SIZE);
	_lenDataTCP = 0;
	_isDisconnectedTCP = false;

	MemTools::set(_sendDataUDP, 0, UDP_PACKET_SIZE);
	_lenDataUDP = 0;
	_clientAddrUDP = NULL;

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

void		ServerClient::addTCPDataToSend(const char *data, const int dataLen)
{
	int		i;
	int		j;

	i = _lenDataTCP;
	j = 0;
	while (j < dataLen && i < TCP_PACKET_SIZE)
	{
		_sendDataTCP[i] = data[j];
		i++;
		j++;
	}
	_lenDataTCP += dataLen;
}

const char	*ServerClient::getSendDataTCP() const
{
	return (&(_sendDataTCP[0]));
}

void		ServerClient::resetDataTCP()
{
	MemTools::set(_sendDataTCP, 0, TCP_PACKET_SIZE);
	_lenDataTCP = 0;
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

struct sockaddr_in *ServerClient::getAddrUDP() const
{
	return (_clientAddrUDP);
}

void		ServerClient::addUDPDataToSend(const char *data, const int dataLen)
{
	int		i;
	int		j;

	i = _lenDataUDP;
	j = 0;
	while (j < dataLen && i < UDP_PACKET_SIZE)
	{
		_sendDataUDP[i] = data[j];
		i++;
		j++;
	}
	_lenDataUDP += dataLen;
}

const char *ServerClient::getSendDataUDP() const
{
	return (&(_sendDataUDP[0]));
}

void ServerClient::resetDataUDP()
{
	MemTools::set(_sendDataUDP, 0, UDP_PACKET_SIZE);
	_lenDataUDP = 0;
}

int ServerClient::getDataLenUDP() const
{
	return (_lenDataUDP);
}

void ServerClient::setAddrUDP(struct sockaddr_in *addr)
{
	_clientAddrUDP = addr;
}

void ServerClient::resetAddrUDP()
{
	_clientAddrUDP = NULL;
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
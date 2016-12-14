#include "ServerClient.hh"

ServerClient::ServerClient(int socketFd)
{
	_TCPSocketFd = socketFd;
	_UDPSocketFd = -1;
	MemTools::set(_sendData, 0, TCP_PACKET_SIZE);
	_lenData = 0;
	MemTools::set(_sendDataUDP, 0, UDP_PACKET_SIZE);
	_lenDataUDP = 0;
	_isDisconnected = false;
}

ServerClient::~ServerClient()
{
}

int			ServerClient::getTCPSocket() const
{
	return (_TCPSocketFd);
}

int			ServerClient::getUDPSocket() const
{
	return (_UDPSocketFd);
}

void		ServerClient::addDataToSend(const char *data, int dataLen)
{
	int		i;
	int		j;

	i = _lenData;
	j = 0;
	while (j < dataLen && i < TCP_PACKET_SIZE)
	{
		_sendData[i] = data[j];
		i++;
		j++;
	}
	_lenData += dataLen;
}

void		ServerClient::addUDPDataToSend(const char *data, int dataLen)
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

const char	*ServerClient::getSendData() const
{
	return (&(_sendData[0]));
}

int			ServerClient::getDataLen() const
{
	return (_lenData);
}

void		ServerClient::resetData()
{
	MemTools::set(_sendData, 0, TCP_PACKET_SIZE);
	_lenData = 0;
}

const char * ServerClient::getSendDataUDP() const
{
	return (&(_sendDataUDP[0]));
}

int ServerClient::getDataLenUDP() const
{
	return (_lenDataUDP);
}

void ServerClient::resetDataUDP()
{
	MemTools::set(_sendDataUDP, 0, TCP_PACKET_SIZE);
	_lenDataUDP = 0;
}

struct sockaddr_in *ServerClient::getAddrUDP() const
{
	return (_clientAddr);
}

bool ServerClient::isDisconnected() const
{
	return (_isDisconnected);
}

void	ServerClient::setDisconnected(bool disconnected)
{
	_isDisconnected = disconnected;
}
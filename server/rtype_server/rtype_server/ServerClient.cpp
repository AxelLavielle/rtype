#include "ServerClient.hh"

ServerClient::ServerClient(int socketFd)
{
	_TCPSocketFd = socketFd;
	MemTools::set(_sendData, 0, TCP_PACKET_SIZE);
	_lenData = 0;
	_isDisconnected = false;
}

ServerClient::~ServerClient()
{
}

int			ServerClient::getTCPSocket() const
{
	return (_TCPSocketFd);
}

const char	*ServerClient::getSendData() const
{
	return (&(_sendData[0]));
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

void		ServerClient::resetData()
{
	MemTools::set(_sendData, 0, TCP_PACKET_SIZE);
	_lenData = 0;
}

int			ServerClient::getDataLen() const
{
	return (_lenData);
}

bool ServerClient::isDisconnected() const
{
	return (_isDisconnected);
}

void	ServerClient::setDisconnected(bool disconnected)
{
	_isDisconnected = disconnected;
}
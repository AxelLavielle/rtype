#include "ASocketClient.hh"


ASocketClient::ASocketClient()
{
	_connected = false;
	_port = -1;
	_ip = "";
}


ASocketClient::~ASocketClient()
{

}

bool ASocketClient::isConnected()
{
	bool	res;

	_mutex.lock();
	res = _connected;
	_mutex.unlock();
	return (res);
}

void ASocketClient::setIp(const std::string & ip)
{
	_mutex.lock();
	_ip = ip;
	_mutex.unlock();
}

void ASocketClient::setPort(const int port)
{
	_mutex.lock();
	_port = port;
	_mutex.unlock();
}

std::string ASocketClient::getIp() const
{
	return (_ip);
}

int ASocketClient::getPort() const
{
	return (_port);
}

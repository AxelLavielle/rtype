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

bool ASocketClient::isConnected() const
{
	return (_connected);
}

void ASocketClient::setIp(const std::string & ip)
{
	_ip = ip;
}

void ASocketClient::setPort(const int port)
{
	_port = port;
}

std::string ASocketClient::getIp() const
{
	return (_ip);
}

int ASocketClient::getPort() const
{
	return (_port);
}

#include "ASocketClient.hh"


ASocketClient::ASocketClient()
{
	_connected = false;
}


ASocketClient::~ASocketClient()
{

}

bool ASocketClient::isConnected() const
{
	return (_connected);
}

#include "ASocketServer.hh"

ASocketServer::ASocketServer()
{
}


ASocketServer::~ASocketServer()
{
}

bool ASocketServer::close()
{
	closesocket(_socketServerID);
	return (true);
}

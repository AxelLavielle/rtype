#include "ASocketServer.hh"

ASocketServer::ASocketServer()
{
}


ASocketServer::~ASocketServer()
{
}

bool ASocketServer::closure()
{
	#ifdef _WIN32
		closesocket(_socketServerID);
	#elif __linux__
		close(_socketServerID);
	#endif
	return (true);
}

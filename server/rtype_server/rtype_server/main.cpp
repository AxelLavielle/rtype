
#include "Server.hh"

int main()
{
	Server	rTypeServer;

	if (rTypeServer.init() == false)
		return (1);
	rTypeServer.launch();
	return (0);
}
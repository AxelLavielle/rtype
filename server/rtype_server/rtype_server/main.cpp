
#include "Server.hh"

int main()
{
	Server	rTypeServer;

	if (rTypeServer.init() == false)
	{
		while (1);
		return (1);
	}
	rTypeServer.launch();
	while (1);
	return (0);
}
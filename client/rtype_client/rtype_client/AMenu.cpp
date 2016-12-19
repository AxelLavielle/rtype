#include "AMenu.hh"

AMenu::AMenu()
{
}


AMenu::~AMenu()
{
}

void AMenu::setGraphManager(IGraphManager * graph)
{
	_graph = graph;
}

void AMenu::setEventManager(IEventManager * event)
{
	_event = event;
}

void AMenu::setSocketTCPSocket(ASocketClient * socket)
{
	_socket = socket;
}

void AMenu::setMutex(AMutex * mutex)
{
	_mutex = mutex;
}
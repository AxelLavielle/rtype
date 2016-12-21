#include "AMenu.hh"

AMenu::AMenu()
{
	_socket = NULL;
	_graph = NULL;
	_event = NULL;
	_mutex = NULL;
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
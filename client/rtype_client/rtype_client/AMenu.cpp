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
	_cmdManager.setSocket(_socket);
}

void AMenu::setMutex(AMutex * mutex)
{
	_mutex = mutex;
	_cmdManager.setMutexSocket(_mutex);
}
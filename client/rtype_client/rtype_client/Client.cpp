#include "Client.hh"



Client::Client()
{
	_socket.init("127.0.0.1", 4242);
	_socket.connectToServer();
}


Client::~Client()
{
	_socket.closure();
	delete _graph;
	delete _event;
	delete _menu;
}

bool Client::launch()
{
	_graph = new SFML();
	_event = new SFMLEvent();
	_menu = new Menu();

	_graph->init();
	_event->setGraphManager(_graph);
	_menu->init();
	_menu->setEventManager(_event);
	_menu->setGraphManager(_graph);
	if (!_menu->launch())
		return (false);
	return (true);
}

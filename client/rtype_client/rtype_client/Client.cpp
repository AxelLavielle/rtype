#include "Client.hh"



Client::Client()
{
}


Client::~Client()
{
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
	_menu->launch();
	return (true);
}

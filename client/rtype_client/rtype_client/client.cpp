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
	if (!_menu->launch())
		return (false);
	while (_graph->isWindowOpen())
	{
		while (_event->refresh())
		{
			if (_event->getCloseEvent() || _event->getKeyStroke() == "ECHAP")
				_graph->close();
		}
		_graph->clearWindow();
		_graph->refresh();
	}
	return (true);
}

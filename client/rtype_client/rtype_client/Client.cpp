#include "Client.hh"



Client::Client()
{
}


Client::~Client()
{
	_socket->closure();
	delete _socket;
	delete _graph;
	delete _event;
	delete _menu;
}

bool Client::initSocket()
{
	_socket = new SocketClientTCP();

	return (true);
	if (!_socket->init("10.16.252.95", 23737)
		|| !_socket->connectToServer())
		return (false);
	return (true);
}

bool	Client::initGraph()
{
	_graph = new SFML();
	_event = new SFMLEvent();
	_menu = new Menu();

	if (!_graph->init())
		return (false);
	_event->setGraphManager(_graph);
	return (true);
}

bool Client::launch()
{
	initSocket();
	if (!initGraph())
		return (false);
	_menu->init();
	_menu->setEventManager(_event);
	_menu->setGraphManager(_graph);
	_menu->setSocketTCPSocket(_socket);
	if (!_menu->launch())
		return (false);
	return (true);
}

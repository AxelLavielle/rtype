#include "Client.hh"

Client::Client()
{
	_pool = new ThreadPool();
	_mutex = new Mutex();
}

Client::~Client()
{
	_socket->closure();
	delete _socket;
	delete _graph;
	delete _event;
	delete _menu;
	delete _pool;
	delete _mutex;
}

bool Client::initSocket()
{
	_mutex->lock();
	_socket = new SocketClientTCP();

	if (!_socket->init("10.16.252.95", 42000)
		|| !_socket->connectToServer())
		return (false);
	_cmdManager.setSocket(_socket);
	_cmdManager.handshake();
	_menu->setSocketTCPSocket(_socket);
	_mutex->unlock();
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
	Thread		th;

	if (!initGraph())
		return (false);
	_menu->init();
	_menu->setEventManager(_event);
	_menu->setGraphManager(_graph);	
	th.createThread(std::bind(&Client::initSocket, this));
	if (!_menu->launch())
		return (false);
	return (true);
}

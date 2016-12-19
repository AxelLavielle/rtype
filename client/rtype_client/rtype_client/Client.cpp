#include "Client.hh"

Client::Client()
{
	_mutex = new Mutex();
	_socket = new SocketClientTCP();
}

Client::~Client()
{
	_socket->closure();
	delete _socket;
	delete _graph;
	delete _event;
	delete _menu;
	delete _mutex;
}

bool Client::initSocket()
{
	_mutex->lock();//10.16.252.95
	if (!_socket->init("10.16.252.95", 42000)
		|| !_socket->connectToServer())
	{
		_menu->setSocketTCPSocket(_socket);
		_mutex->unlock();
		return (false);
	}
	_menu->setSocketTCPSocket(_socket);
	_cmdManager.setSocket(_socket);
	_cmdManager.handshake();
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
	_menu->setEventManager(_event);
	_menu->setGraphManager(_graph);
	_menu->setMutex(_mutex);
	_menu->init();
	th.createThread(std::bind(&Client::initSocket, this));
	_pool.addThread(&th);
	if (!_menu->launch())
	{
		_pool.joinAll();
		return (false);
	}
	_pool.joinAll();
	return (true);
}

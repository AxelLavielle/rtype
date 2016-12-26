#include "Client.hh"

Client::Client()
{
	_mutex = new Mutex();
	_socket = new SocketClientTCP();
	//_ip = "127.0.0.1";
	_ip = "10.16.252.95";
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
	_mutex->lock();
	if (!_socket->init(_ip, 42000)
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
	SocketClientUDP		udpSocket;
	BasicCmd			*cmd = new BasicCmd();
	
	if (!initGraph())
		return (false);
	_menu->setIp(_ip);
	_menu->setPort(42000);
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

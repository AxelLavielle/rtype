#include "Client.hh"

Client::Client()
{
	SaveConfig sv;

	sv.readFromFile();
	sv.writeToFile();
	_mutex = new Mutex();
	_socket = new SocketClientTCP();
	//_ip = "127.0.0.1";
//	_ip = "10.16.252.95"; // Sarah
//	_ip = "10.16.253.119"; // Anthony
	//_ip = "10.16.252.135"; // Momo
//	_ip = "10.16.253.15"; // Alexis
	_ip = sv.getIport().substr(0, sv.getIport().find(":"));
	_port = std::stoi(sv.getIport().substr(sv.getIport().find(":") + 1));
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
	if (!_socket->init(_ip, _port)
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

	if (!initGraph())
		return (false);
	_menu->setIp(_ip);
	_menu->setPort(_port);
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

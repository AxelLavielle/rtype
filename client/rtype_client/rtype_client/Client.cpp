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
	SocketClientUDP		udpSocket;
	BasicCmd			*cmd = new BasicCmd();
	// ICommand			*newCmd;
	// BasicCmd			*b;
	// char				*res;

	
	cmd->setCommandType(REPLY_CODE);
	cmd->addArg("4242");
	cmd->addArg("COUCOU");
	if (!udpSocket.init("10.16.252.95", 9999) || !udpSocket.connectToServer())
		return (false);
	udpSocket.sendData(Serialize::serialize(cmd), sizeof(*cmd));
	//res = udpSocket.receiveData();
	//newCmd = Serialize::unserializeCommand(res);
	//b = static_cast<BasicCmd* >(newCmd);
	//std::cout << b->getArg(0) << std::endl;
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
		_socket->closure();
		return (false);
	}
	_pool.joinAll();
	_socket->closure();
	return (true);
}

#include "Game.hh"



Game::Game()
{
	_size.first = 0;
	_size.second = 0;
	_dificulty = 0;
	_fileManager.init();
	_musicStage1.setDuration(-1);
	_musicStage1.setLoop(true);
	_musicStage1.setMusic(true);
	_musicStage1.setFilePath(_fileManager.getRoot() + "/res/sounds/stage1.wav");
	_input = new InputCmd();
	_sock = new SocketClientUDP();
	_id = -1;
	_ip = "";
	_port = -1;
}

Game::~Game()
{
	std::vector<IGUIElement* >::iterator		it;

	it = _guiElement.begin();
	while (it != _guiElement.end())
	{
		delete (*it);
		++it;
	}
	_guiElement.clear();
}

bool Game::initSocket()
{
	if (!_sock->init(_ip, _port) || !_sock->connectToServer())
		return (false);
	_cmdManager.setUDPSocket(_sock);
	if (!_cmdManager.sendLaunchGame(_id))
		return (false);
	return (true);
}

void	Game::initGraphElements()
{
	_graph->setFullScreen(true);
	_graph->setMouseCursorVisible(false);
	_size = _graph->getWindowSize();
	_guiPage = new GUIPage(_graph, _event, _fileManager, &_soundManager);
	_guiPage->init();
}

void	Game::manageEntity()
{
	IEntity *entity = new Player();
	IEntity	*newEntity;
	char *res;

	entity->setPosX(10);
	entity->setPosY(10);
	entity->setWidth(50);
	entity->setHeight(50);
	entity->setSpriteRepo("/res/img");
	res = Serialize::serialize(entity);
	newEntity = Serialize::unserializeEntity(res);
	_guiPage->draw();
	std::cout << "x = " << newEntity->getPosX() << "y = " << newEntity->getPosY() << "height = " << entity->getHeight() << "width = " << entity->getWidth() << std::endl;
	_graph->drawRectangle(_fileManager.getRoot() + newEntity->getSpriteRepo() + "spaceShip10.png", Rect(newEntity->getPosX(), newEntity->getPosY(), 0, 0), Rect(0, 0, entity->getHeight(), entity->getWidth()));
	delete entity;
	delete newEntity;
	delete res;
}

int Game::launch()
{
	std::chrono::high_resolution_clock::time_point      t1;
	std::chrono::high_resolution_clock::time_point	    t2;
	 double												duration;
	 int													i;
	 bool												first = true;

	 i = 100;
	 if (!initSocket())
	 {
		 std::cerr << "ERROR: connexion udp socket" << std::endl;
		 return (0);
	 }
	 initGraphElements();
	 t1 = std::chrono::high_resolution_clock::now();
	 _soundManager.play(_musicStage1);
//	 _cmdManager.receiveUDPCmd();
	while (_graph->isWindowOpen())
	{
		while (_event->refresh())
		{
			if (_event->getCloseEvent())
				return (1);
			if (_guiPage->event() == IPage::QUIT)
				return (0);
			if (_event->getKeyStroke() == "UP" || _event->getKeyStroke() == "LEFT"
				|| _event->getKeyStroke() == "DOWN" || _event->getKeyStroke() == "RIGHT")
				_cmdManager.sendInput(_event->getKeyStroke());
			
			if (_event->getKeyStroke() == "ECHAP")
			{
				delete _guiPage;
				_guiPage = new PausePage(_graph, _event, _fileManager, &_soundManager);
				_guiPage->init();
			}

		}
		t2 = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
		if (first || duration >= 10000)
		{
			i += 10;
			if (i >= 1000)
				i = 0;
			first = false;
			t1 = std::chrono::high_resolution_clock::now();
		}
		_graph->clearWindow();
		_graph->setBackground(_fileManager.getRoot() + "/res/img/stars_background.jpg", -1, -1);
		_graph->drawRectangle(Color(255, 255, 255), Rect(i, 300, 50, 50));
		manageEntity();
		_graph->refresh();
	}
	return (0);
}

void Game::setGraph(IGraphManager * graph)
{
	_graph = graph;
}

void Game::setEvent(IEventManager * event)
{
	_event = event;
}

void Game::setIp(const std::string & ip)
{
	_ip = ip;
}

void Game::setPort(const int port)
{
	_port = port;
}

void Game::setId(const int id)
{
	_id = id;
}

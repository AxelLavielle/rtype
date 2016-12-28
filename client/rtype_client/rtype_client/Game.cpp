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
	_playerName = "";
	_port = -1;
	_nbPlayer = 0;
	_run = true;
	_mode = "Easy";
	_key = "";
	_newEvent = true;
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
	return (true);
}

void	Game::initGraphElements()
{
	GUIPage			*gui;

	_graph->setFullScreen(true);
	_graph->setMouseCursorVisible(false);
	_size = _graph->getWindowSize();
	gui = new GUIPage(_graph, _event, _fileManager, &_soundManager);
	gui->setPlayerName(_playerName);
	gui->setNbPlayer(_nbPlayer);
	gui->setMode(_mode);
	_guiPage = gui;
	_guiPage->init();
	_windowGameSize.first = _windowSize.first;
	_windowGameSize.second = _windowSize.second - (gui->getBottomBarHeight() + gui->getTopBarHeight());
}

void	Game::manageEntity()
{
	std::chrono::high_resolution_clock::time_point		tGame;
	std::chrono::high_resolution_clock::time_point	    tGame2;
	IEntity												*entity;
	double												duration;

	tGame = std::chrono::high_resolution_clock::now();
	while (1)
	{
		tGame2 = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::milliseconds>(tGame2 - tGame).count();
		if (duration >= RECEIVE_DURATION)
			tGame = std::chrono::high_resolution_clock::now();
		else
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<unsigned long>((GAME_LOOP_DURATION - duration))));
		_mutexRun.lock();
		if (!_run)
		{
			_mutexRun.unlock();
			return;
		}
		_mutexRun.unlock();
		if ((entity = _cmdManager.receiveUDPCmd()) != NULL)
		{
			_mutex.lock();
			_newEvent = true;
			_entity.push_back(entity);
			_mutex.unlock();
		}
	}
}

int Game::launch()
{
	std::chrono::high_resolution_clock::time_point		tGame;
	std::chrono::high_resolution_clock::time_point	    tGame2;
	std::chrono::high_resolution_clock::time_point		t1;
	std::chrono::high_resolution_clock::time_point	    t2;
	double												duration;
	 int												i;
	 bool												first = true;
	 Thread												*th;

	 i = 100;
	 if (!initSocket())
	 {
		 std::cerr << "ERROR: connexion udp socket" << std::endl;
		 return (0);
	 }
	 initGraphElements();
	 tGame = std::chrono::high_resolution_clock::now();
	 t1 = std::chrono::high_resolution_clock::now();
	 _soundManager.play(_musicStage1);
	 th = new Thread();
	 th->createThread(std::bind(&Game::manageEntity, this));
	 _pool.addThread(th);
	while (_graph->isWindowOpen())
	{
		tGame2 = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::milliseconds>(tGame2 - tGame).count();
		if (duration >= GAME_LOOP_DURATION)
			tGame = std::chrono::high_resolution_clock::now();
		else
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<unsigned long>((GAME_LOOP_DURATION - duration))));

		t2 = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
		if (_key != "" && duration >= INPUT_DURATION)
		{
			t1 = std::chrono::high_resolution_clock::now();
			std::cout << "duration = " << duration << std::endl;
			_cmdManager.sendInput(_id, _key);
		}

		while (_event->refresh())
		{
			if (_event->getCloseEvent() || _guiPage->event() == IPage::QUIT)
			{
				_mutexRun.lock();
				_run = false;
				_mutexRun.unlock();
				_pool.joinAll();
				return (1);
			}
			if (_event->getKeyReleased() == _key)
				_key = "";
			if (_key == "" && (_event->getKeyStroke() == "UP" || _event->getKeyStroke() == "LEFT"
				|| _event->getKeyStroke() == "DOWN" || _event->getKeyStroke() == "RIGHT"))
			{
				_key = _event->getKeyStroke();
				_cmdManager.sendInput(_id, _event->getKeyStroke());
			}
			if (_event->getKeyStroke() == "ECHAP")
			{
				delete _guiPage;
				_guiPage = new PausePage(_graph, _event, _fileManager, &_soundManager);
				_guiPage->init();
			}
		}

		if (_newEvent)
		{
			_graph->clearWindow();
			_graph->setBackground(_fileManager.getRoot() + "/res/img/stars_background.jpg", -1, -1);

			std::vector<IEntity* >::iterator		it;

			_mutex.lock();
			it = _entity.begin();
			//std::cout << _entity.size() << std::endl;
			while (it != _entity.end())
			{
				_graph->drawRectangle(_fileManager.getRoot() + (*it)->getSpriteRepo(),
					Rect((*it)->getPosX() * (_windowGameSize.first / NB_CELL_X),
					(*it)->getPosY() * (_windowGameSize.second / NB_CELL_Y) + static_cast<GUIPage *>(_guiPage)->getTopBarHeight(),
					(*it)->getHeight() * (_windowGameSize.second / NB_CELL_Y),
					(*it)->getWidth() * (_windowGameSize.first / NB_CELL_X)),
					Color(0, 0, 0));
				delete *it;
				++it;
			}
			_entity.clear();
			_mutex.unlock();
			_guiPage->draw();
			_graph->refresh();
			_newEvent = false;
		}
	}
	_mutexRun.lock();
	_run = false;
	_mutexRun.unlock();
	_pool.joinAll();
	return (0);
}

void Game::setGraph(IGraphManager * graph)
{
	_graph = graph;
	_windowSize = _graph->getWindowSize();
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

void Game::setNbPlayer(const int nb)
{
	_nbPlayer = nb;
}

#include "AGUIElement.hh"
#include "Menu.hh"

Menu::Menu()
{
}

Menu::~Menu()
{
}

bool Menu::init()
{
	_music.setDuration(-1);
	_music.setMusic(true);
	if (!_fileManager.init())
		return (false);
	_music.setFilePath(_fileManager.getRoot() + "/res/sounds/opening.wav");
	_music.setLoop(true);
	_clickSound.setDuration(-1);
	_clickSound.setFilePath(_fileManager.getRoot() + "/res/sounds/buttonClick.wav");
	_soundManager.play(_music);
	_t1Conn = std::chrono::high_resolution_clock::now();
	return (true);
}

void	Menu::initLobby()
{
	LobbyPage		*page;

	page = new LobbyPage(_graph, _event, _fileManager, &_soundManager);
	page->addRoom("ROOM 1");
	page->addRoom("ROOM 2");
	page->addRoom("ROOM 3");
	page->addRoom("ROOM 4");
	page->addRoom("ROOM 5");
	page->addRoom("ROOM 6");
	page->addRoom("ROOM 7");
	page->addRoom("ROOM 8");
	page->addRoom("ROOM 9");
	page->addRoom("ROOM 10");
	page->addRoom("ROOM 11");
	page->addRoom("ROOM 12");
	page->addRoom("ROOM 13");
	page->addRoom("ROOM 14");
	page->addRoom("ROOM 15");
	_page = page;
}

bool Menu::tryToConnect()
{
	bool	res;

	res = false;
	_mutex->lock();
	if (_socket)
		std::cout << "SOCKET EXIST !!" << std::endl;
	else
		std::cout << "SOCKET NOT EXIST !!" << std::endl;
	if (_socket && !_socket->isConnected())
	{
		std::cout << "TRY TO CONNECT" << std::endl;
		_socket->init("127.0.0.1", 42000);
		_socket->connectToServer();
	}
	if (_socket)
		res = _socket->isConnected();
	_mutex->unlock();
	return (res);
}

bool Menu::launch()
{
  IPage::PAGE	curr_event;
  _page = new HomePage(_graph, _event, _fileManager, &_soundManager);
  bool		newEvent;
  Thread		*th = NULL;
  std::chrono::high_resolution_clock::time_point        t2Conn;
  double				duration;

  newEvent = false;
  _page->init();
  while (_graph->isWindowOpen())
    {
	  
	  t2Conn = std::chrono::high_resolution_clock::now();
	  duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2Conn - _t1Conn).count();;
	  if (duration >= RECO_DURATION)
	  {
		  std::cout << "COUCOU = " << duration << std::endl;
		  if (_mutex->tryLock() && _socket && !_socket->isConnected())
		  {
			  if (th)
			  {
				  th->join();
				  _pool.removeThread(th);
			  }
			  th = new Thread();
			  th->createThread(std::bind(&Menu::tryToConnect, this));
			  _pool.addThread(th);
			  _t1Conn = std::chrono::high_resolution_clock::now();
			  _mutex->unlock();
		  }
	  }

	  while (_event->refresh())
		{
		  curr_event = _page->event();
		  if (_page->getPageType() == IPage::PLAY)
		  {
			  LobbyPage		*lobbyPage;

			  lobbyPage = static_cast<LobbyPage* >(_page);
			  if (lobbyPage->getSelectedRoom() != -1)
				  std::cout << "selected = " << lobbyPage->getSelectedRoom() << std::endl;
		  }
		  switch (curr_event)
		    {
		    case IPage::HOME:
		      delete (_page);
		      newEvent = true;
		      _page = new HomePage(_graph, _event, _fileManager, &_soundManager);
		      std::cout << "Home" << std::endl;
		      break;
		    case IPage::PLAY:
		      delete (_page);
		      newEvent = true;
			  initLobby();
		      std::cout << "Lobby" << std::endl;
		      break;
		    case IPage::CREATEROOM:
		      delete (_page);
		      newEvent = true;
		      _page = new CreateRoomPage(_graph, _event, _fileManager, &_soundManager);
		      std::cout << "RoomList" << std::endl;
		      break;
		    case IPage::INSIDEROOM:
		      delete (_page);
		      newEvent = true;
		      _page = new InsideRoomPage(_graph, _event, _fileManager, &_soundManager);
		      std::cout << "InsideRoom" << std::endl;
		      break;
		    case IPage::SETTINGS:
		      delete (_page);
		      newEvent = true;
		      _page = new SettingsPage(_graph, _event, _fileManager, &_soundManager);
		      std::cout << "Settings" << std::endl;
		      break;
			case IPage::GAME:
				delete (_page);
				std::cout << "Game" << std::endl;
				newEvent = true;
				_soundManager.stopAll();
				_game.setGraph(_graph);
				_game.setEvent(_event);
				_game.launch();
				_pool.joinAll();
				return (true);
				break;
			case IPage::ENDGAME:
				delete (_page);
				newEvent = true;
				_page = new EndGamePage(_graph, _event, _fileManager, &_soundManager);
				std::cout << "Settings" << std::endl;
				break;
			    case IPage::QUIT:
		     _graph->close();
		      break;
			default:
			   break;
	    }
	  if (_event->getKeyStroke() == "ECHAP" || _event->getCloseEvent())
	    _graph->close();
	  if (newEvent)
	    {
	      _page->init();
	      _graph->clearWindow();
	      _page->draw();
	      _graph->refresh();
	      newEvent = false;
	    }
	}
      _graph->clearWindow();
      _page->draw();
      _graph->refresh();
    }
  _pool.joinAll();
  return (false);
}

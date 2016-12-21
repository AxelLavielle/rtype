#include "AGUIElement.hh"
#include "Menu.hh"

Menu::Menu()
{
	_playerName = "Player 1";
	_newEvent = false;
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
			      _soundManager.setMusicVolume(100);
			      _soundManager.setSoundVolume(100);
	_soundManager.play(_music);
	_t1Conn = std::chrono::high_resolution_clock::now();
	_cmdManager.setSocket(_socket);
	return (true);
}

void	Menu::initLobby()
{
	LobbyPage		*page;
	ListRoomCmd		*cmd;
	std::vector<RoomIdInfos>		rooms;
	std::vector<RoomIdInfos>::iterator		it;

	page = new LobbyPage(_graph, _event, _fileManager, &_soundManager);
	_page = page;
	if (!_socket)
		return;
	_cmdManager.setSocket(_socket);
	if (!(cmd = _cmdManager.getRoomList()))
		return;
	std::cout << "Got rooom list" << std::endl;
	rooms = cmd->getAllRooms();
	it = rooms.begin();
	while (it != rooms.end())
	{
		page->addRoom(*it);
		++it;
	}
}

bool Menu::tryToConnect()
{
	bool	res;

	res = false;
	_mutex->lock();
	if (_socket && !_socket->isConnected())
	{
		std::cout << "TRY TO CONNECT" << std::endl;
		_socket->init("127.0.0.1", 42000);
		_socket->connectToServer();
		if (_socket->isConnected())
		{
			_cmdManager.setSocket(_socket);
			_cmdManager.handshake();
		}
	}
	if (_socket)
		res = _socket->isConnected();
	_mutex->unlock();
	return (res);
}

void	Menu::manageReco(Thread *th)
{
	std::chrono::high_resolution_clock::time_point      t2Conn;
	double												duration;

	t2Conn = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2Conn - _t1Conn).count();
	if (duration >= RECO_DURATION)
	{
		if (_socket && !_socket->isConnected())
		{
			if (th)
			{
				_pool.joinAll();
				_pool.removeThread(th);
			}
			th = new Thread();
			th->createThread(std::bind(&Menu::tryToConnect, this));
			_pool.addThread(th);
		}
		_t1Conn = std::chrono::high_resolution_clock::now();
	}
}

void	Menu::setRoomInfo(RoomInfoCmd *roomInfo, InsideRoomPage *page)
{
	std::vector<PlayerInfo>					pl;
	std::vector<PlayerInfo>::iterator		it;

	it = pl.begin();
	page->setRoomName(roomInfo->getName());
	while (it != pl.end())
	{
		page->addPlayer(it->first, it->second);
		++it;
	}
}

bool Menu::launch()
{
  IPage::PAGE	curr_event;
  _page = new HomePage(_graph, _event, _fileManager, &_soundManager);
  bool		_newEvent;
  Thread		*th = NULL;
  std::pair<std::string, std::pair<int, int> > tmp;

  _newEvent = false;
  _page->init();
  while (_graph->isWindowOpen())
    {
	  manageReco(th);
	  while (_event->refresh())
		{
		  curr_event = _page->event();


		  if (_page->getPageType() == IPage::PLAY)
		  {
			  LobbyPage		*lobbyPage;

			  lobbyPage = static_cast<LobbyPage* >(_page);
			  if (lobbyPage->getSelectedRoom().first != -84)
			  {
				  std::cout << lobbyPage->getSelectedRoom().first << std::endl;
				  if (!_cmdManager.joinRoom(lobbyPage->getSelectedRoom().first, _playerName))
					  std::cerr << "Can not join room" << std::endl;
				  else
				  {
					  RoomInfoCmd			*roomInfo1;

					  delete _page;
					  _newEvent = true;
					  _page = new InsideRoomPage(_graph, _event, _fileManager, &_soundManager);

					  roomInfo1 = _cmdManager.getRoomInfo();
					  setRoomInfo(roomInfo1, (static_cast<InsideRoomPage*>(_page)));
				  }
			  }
		  }

		  switch (curr_event)
		    {
		    case IPage::HOME:
		      delete (_page);
		      _newEvent = true;
		      _page = new HomePage(_graph, _event, _fileManager, &_soundManager);
		      std::cout << "Home" << std::endl;
		      break;
		    case IPage::PLAY:
				if (_page->getPageType() == IPage::INSIDEROOM)
					_cmdManager.leaveRoom();
		      delete (_page);
			  _newEvent = true;
			  initLobby();
		      std::cout << "Lobby" << std::endl;
		      break;
		    case IPage::SAVE:
				SettingsPage	*tmpPageSettings;
				tmpPageSettings = static_cast<SettingsPage *>(_page);
		      tmp = static_cast<SettingsPage *>(_page)->save();
		      //_soundManager.setMusicVolume(tmp.second.first);
		      //_soundManager.setSoundVolume(tmp.second.second);
			  _mutex->lock();
			  if (_socket)
			  {
				  _socket->setIp(tmpPageSettings->getServerInfo().first);
				  _socket->setPort(tmpPageSettings->getServerInfo().second);
			  }
			  _mutex->unlock();
		      break;
		    case IPage::CREATEROOM:
		      delete (_page);
		      _newEvent = true;
		      _page = new CreateRoomPage(_graph, _event, _fileManager, &_soundManager);
		      std::cout << "RoomList" << std::endl;
		      break;
		    case IPage::INSIDEROOM:
		      delete (_page);
			  _newEvent = true;
		      _page = new InsideRoomPage(_graph, _event, _fileManager, &_soundManager);
			  std::cout << "InsideRoom" << std::endl;
			  break;
		    case IPage::PAUSE:
		      delete (_page);
		      _newEvent = true;
		      _page = new PausePage(_graph, _event, _fileManager, &_soundManager);
		      std::cout << "Pause" << std::endl;
		      break;
		    case IPage::SETTINGS:
		      delete (_page);
		      _newEvent = true;
			  SettingsPage *tmpSettings;
		      tmpSettings = new SettingsPage(_graph, _event, _fileManager, &_soundManager);
			  tmpSettings->setServerInfo(_ip, _port);
			  _page = tmpSettings;
		      std::cout << "Settings" << std::endl;
		      break;
		    case IPage::SETTINGSNEXT:
		      delete (_page);
		      _newEvent = true;
		      _page = new SettingsNextPage(_graph, _event, _fileManager, &_soundManager);
		      std::cout << "SettingsNext" << std::endl;
		      break;
			case IPage::GAME:
				_cmdManager.launchGame();
				_newEvent = true;
				delete (_page);
				std::cout << "Game" << std::endl;
				_soundManager.stopAll();
				_game.setGraph(_graph);
				_game.setEvent(_event);
				_game.setPort(_port);
				_game.setIp(_ip);
				_pool.joinAll();
				_socket->closure();
				_game.launch();
				std::cout << "QUIT LA" << std::endl;
				return (true);
				break;
			case IPage::ENDGAME:
				delete (_page);
				_newEvent = true;
				_page = new EndGamePage(_graph, _event, _fileManager, &_soundManager);
				std::cout << "Settings" << std::endl;
				break;
			case IPage::QUIT:
				_graph->close();
				break;
			case IPage::CREATEROOMACTION:
				_newEvent = true;
				std::cout << "CreateRoomAction" << std::endl;
				CreateRoomPage		*tmpPage;
				tmpPage = static_cast<CreateRoomPage* >(_page);
				if (!_cmdManager.createRoom(tmpPage->getRoomName(), "Player 1"))
				{
					std::cerr << "Cannot create room" << std::endl;
					break;
				}
				delete (_page);
				_page = new InsideRoomPage(_graph, _event, _fileManager, &_soundManager);
				break;
			default:
			   break;
	    }
	  if (_event->getKeyStroke() == "ECHAP" || _event->getCloseEvent())
	    _graph->close();
	  if (_newEvent)
	    {
	      _page->init();
	      _graph->clearWindow();
	      _page->draw();
	      _graph->refresh();
	      _newEvent = false;
	    }
	}
      _graph->clearWindow();
      _page->draw();
      _graph->refresh();
    }
	std::cout << "QUIT LA2" << std::endl;
	_pool.joinAll();
  return (false);
}

void Menu::setIp(const std::string & ip)
{
	_ip = ip;
}

void Menu::setPort(const int port)
{
	_port = port;
}

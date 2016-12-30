#include "AGUIElement.hh"
#include "Menu.hh"

Menu::Menu()
{
	SaveConfig		sv;

	sv.readFromFile();
	_playerName = "Player 1";
	_newEvent = false;
	_roomInfo = new RoomInfoCmd();
	_run = true;
	_id = -1;
	_th = NULL;
	_checkGameReady = false;
}

Menu::~Menu()
{
	delete _roomInfo;
}

bool Menu::init()
{
	_graph->setFullScreen(true);
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
	std::cout << "Got rooom list" << static_cast<int>(cmd->getCommandName()) << std::endl;
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
		_socket->init(_ip, 42000);
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

	pl = roomInfo->getPlayersList();
	page->setRoomName(roomInfo->getName());
	it = pl.begin();
	while (it != pl.end())
	{
		page->addPlayer(it->first, it->second);
		++it;
	}
}

void	Menu::receiveData()
{
	RoomInfoCmd		*roomInfo;

	while (1)
	{
		_mutexRun.lock();
		if (!_run)
		{
			_mutexRun.unlock();
			return;
		}
		_mutexRun.unlock();
		//if (_roomInfo)
			//delete (_roomInfo);
		std::cout << "LISTEN" << std::endl;
		if (_cmdManager.updateRoom())
		{
			std::cout << "UPDATE ROOM RECEIVE" << std::endl;
			roomInfo = _cmdManager.getRoomInfo();
			if (roomInfo)
			{
				_mutexReceive.lock();
				_roomInfo = roomInfo;
				_mutexReceive.unlock();
			}
		}
	}
}

void	Menu::checkGameReady()
{
	int				res;

	while (1)
	{
		_mutexRun.lock();
		if (!_run || !_checkGameReady)
		{
			_mutexRun.unlock();
			return;
		}
		_mutexRun.unlock();
		if ((res = _cmdManager.launchGame()) != -1)
		{
			_mutexReceive.lock();
			std::cout << "SET ID = " << _id << std::endl;
			_id = res;
			_mutexReceive.unlock();
			return;
		}
	}
}

void	Menu::manageLaunchGame()
{
	_th = new Thread();
	_newEvent = true;
	if (_checkGameReady)
		return;
	_checkGameReady = true;
	_cmdManager.setStatus();
	_th->createThread(std::bind(&Menu::checkGameReady, this));
	_pool.addThread(_th);
	_mutexReceive.lock();
	if (_id == -1)
	{
		_mutexReceive.unlock();
		return;
	}
	delete (_page);
	std::cout << "Game" << std::endl;
	_soundManager.stopAll();
	_game.setGraph(_graph);
	_game.setEvent(_event);
	_game.setPort(9999);
	_game.setId(_id);
	_game.setIp(_ip);
	if (_roomInfo)
		_game.setNbPlayer(_roomInfo->getPlayersList().size());
	_mutexReceive.unlock();
	_mutexRun.lock();
	_run = false;
	_mutexRun.unlock();
	_pool.joinAll();
	_socket->closure();
	_game.launch();
}

bool Menu::launch()
{
  IPage::PAGE									curr_event;
  _page = new HomePage(_graph, _event, _fileManager, &_soundManager);
  bool											_newEvent;
  Thread										*th = NULL;
  std::pair<std::string, std::pair<int, int> >	tmp;

  _newEvent = false;
  _page->init();
  while (_graph->isWindowOpen())
    {
	  manageReco(th);

	  if (_page->getPageType() == IPage::INSIDEROOM)
	  {
		  _mutexReceive.lock();
		  //_page->clear();
		  if (_roomInfo)
			  setRoomInfo(_roomInfo, (static_cast<InsideRoomPage*>(_page)));
		  _page->init();
		  _mutexReceive.unlock();
	  }

	  _mutexReceive.lock();
	  if (_id != -1)
	  {
		  delete (_page);
		  std::cout << "Game" << std::endl;
		  _soundManager.stopAll();
		  _game.setGraph(_graph);
		  _game.setEvent(_event);
		  _game.setPort(9999);
		  _game.setId(_id);
		  _game.setIp(_ip);
		  if (_roomInfo)
			  _game.setNbPlayer(_roomInfo->getPlayersList().size());
		  _mutexRun.lock();
		  _run = false;
		  _mutexRun.unlock();
		  _pool.joinAll();
		  _game.launch();
		  _mutexReceive.unlock();
		  std::cout << "Je QUIT LA" << std::endl;
		  return (1);
	  }
	  _mutexReceive.unlock();

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
					  Thread				*th2;

					  delete _page;
					  _newEvent = true;
					  _page = new InsideRoomPage(_graph, _event, _fileManager, &_soundManager);

					  roomInfo1 = _cmdManager.getRoomInfo();
					  setRoomInfo(roomInfo1, (static_cast<InsideRoomPage*>(_page)));
					  _page->clear();
					  _page->init();
					  th2 = new Thread();
					  th2->createThread(std::bind(&Menu::receiveData, this));
					  _pool.addThread(th2);
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
				{
					_cmdManager.leaveRoom();
				}
		      delete (_page);
			  _newEvent = true;
			  initLobby();
		      std::cout << "Lobby" << std::endl;
		      break;
		    case IPage::SAVE:
				//SettingsPage	*tmpPageSettings;
				//tmpPageSettings = static_cast<SettingsPage *>(_page);
				tmp = static_cast<SettingsPage *>(_page)->save();
				//_soundManager.setMusicVolume(tmp.second.first);
				//_soundManager.setSoundVolume(tmp.second.second);
				//_mutex->lock();
				//if (_socket)
				//{
				//	  _socket->setIp(tmpPageSettings->getServerInfo().first);
				//	  _socket->setPort(tmpPageSettings->getServerInfo().second);
				//}
				//_mutex->unlock();
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
				std::cout << "wait launch game" << std::endl;
				manageLaunchGame();
				_mutexReceive.lock();
				if (_id != -1)
				{
					_mutexReceive.unlock();
					_mutexRun.lock();
					_run = false;
					_mutexRun.unlock();
					_pool.joinAll();
					return (true);
				}
				_mutexReceive.unlock();
				std::cout << "QUIT LA" << std::endl;
				break;
			case IPage::ENDGAME:
				delete (_page);
				_newEvent = true;
				_page = new PausePage(_graph, _event, _fileManager, &_soundManager);
				std::cout << "Settings" << std::endl;
				break;
			case IPage::LOADING:
				delete (_page);
				_newEvent = true;
				_page = new LoadingPage(_graph, _event, _fileManager, &_soundManager);
				std::cout << "Loading" << std::endl;
				break;
			case IPage::QUIT:
				_graph->close();
				break;
			case IPage::CREATEROOMACTION:
				std::cout << "CreateRoomAction1" << std::endl;
				_newEvent = true;
				CreateRoomPage		*tmpPage;
				tmpPage = static_cast<CreateRoomPage* >(_page);
				if (!_cmdManager.createRoom(tmpPage->getRoomName(), "Player 1"))
				{
					std::cerr << "Cannot create room" << std::endl;
					break;
				}
				std::cout << "CreateRoomAction2" << std::endl;
				delete (_page);
				RoomInfoCmd			*roomInfo1;

				_page = new InsideRoomPage(_graph, _event, _fileManager, &_soundManager);
				roomInfo1 = _cmdManager.getRoomInfo();
				setRoomInfo(roomInfo1, (static_cast<InsideRoomPage*>(_page)));
				_page->clear();
				_page->init();
				break;
			default:
			   break;
	    }
	  if (_event->getCloseEvent())
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

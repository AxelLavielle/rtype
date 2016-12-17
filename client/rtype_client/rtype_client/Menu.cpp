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
	return (true);
}

bool Menu::launch()
{
  IPage::PAGE	curr_event;
  APage	*pages = new HomePage(_graph, _event, _fileManager, &_soundManager);
  bool		newEvent;

  newEvent = false;
  pages->init();
  while (_graph->isWindowOpen())
    {
      while (_event->refresh())
	{
	  curr_event = pages->event();
	  switch (curr_event)
	    {
	    case IPage::HOME:
	      delete (pages);
	      newEvent = true;
	      pages = new HomePage(_graph, _event, _fileManager, &_soundManager);
	      std::cout << "Home" << std::endl;
	      break;
	    case IPage::PLAY:
	      delete (pages);
	      newEvent = true;
	      pages = new LobbyPage(_graph, _event, _fileManager, &_soundManager);
	      std::cout << "Lobby" << std::endl;
	      break;
	    case IPage::ROOMLIST:
	      delete (pages);
	      newEvent = true;
	      pages = new RoomListPage(_graph, _event, _fileManager, &_soundManager);
	      std::cout << "RoomList" << std::endl;
	      break;
	    case IPage::INSIDEROOM:
	      delete (pages);
	      newEvent = true;
	      pages = new InsideRoomPage(_graph, _event, _fileManager, &_soundManager);
	      std::cout << "InsideRoom" << std::endl;
	      break;
	    case IPage::SETTINGS:
	      delete (pages);
	      newEvent = true;
	      pages = new SettingsPage(_graph, _event, _fileManager, &_soundManager);
	      std::cout << "Settings" << std::endl;
	      break;
		case IPage::GAME:
			delete (pages);
			std::cout << "Game" << std::endl;
			newEvent = true;
			_soundManager.stopAll();
			_game.setGraph(_graph);
			_game.setEvent(_event);
			_game.launch();
			return (true);
			break;
			//case IPage::ENDGAME:
		//	delete (pages);
		//	newEvent = true;
		//	pages = new EndPage(_graph, _event, _fileManager, &_soundManager);
		//	std::cout << "Settings" << std::endl;
		//	break;
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
	      pages->init();
	      _graph->clearWindow();
	      pages->draw();
	      _graph->refresh();
	      newEvent = false;
	    }
	}
      _graph->clearWindow();
      pages->draw();
      _graph->refresh();
    }
  return (false);
}

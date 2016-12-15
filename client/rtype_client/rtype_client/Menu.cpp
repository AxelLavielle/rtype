#include "AGUIElement.hh"
#include "Menu.hh"

Menu::Menu()
{
	_pagenb = PAGE::ACCEUIL;
	_animInc = 0;
	_first = true;
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

  pages->init();
  while (_graph->isWindowOpen())
    {
      while (_event->refresh())
	{
	  curr_event = pages->event();
	  switch (curr_event)
	    {
	    case IPage::HOME:
	      pages = new HomePage(_graph, _event, _fileManager, &_soundManager);
	      delete (pages);
	      break;
	    case IPage::PLAY:
	      delete (pages);
	      pages = new LobbyPage(_graph, _event, _fileManager, &_soundManager);
	      break;
	    case IPage::ROOMLIST:
	      delete (pages);
	      pages = new RoomListPage(_graph, _event, _fileManager, &_soundManager);
	      break;
	    case IPage::INSIDEROOM:
	      delete (pages);
	      pages = new InsideRoomPage(_graph, _event, _fileManager, &_soundManager);
	      break;
	    case IPage::SETTINGS:
	      break;
	    case IPage::QUIT:
	      _graph->close();
	      break;
	    default:
	      break;
	    }
	  if (_event->getKeyStroke() == "ECHAP" || _event->getCloseEvent())
	    _graph->close();
	}
      _graph->clearWindow();
      pages->draw();
      _graph->refresh();
    }
  return (false);
}

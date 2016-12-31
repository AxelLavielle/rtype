#include "LobbyPage.hh"

LobbyPage::LobbyPage(IGraphManager *graph, IEventManager *event, const PathFileManager &fileManager, ISoundManager *soundManager) : APage(graph, event, fileManager, soundManager)
{
	_backgroundSprite = _fileManager.getRoot() + "/res/img/background_menu2.jpg";
	_clickSound.setDuration(-1);
	_clickSound.setFilePath(_fileManager.getRoot() + "/res/sounds/buttonClick.wav");
	_pageType = IPage::PLAY;
}

LobbyPage::~LobbyPage()
{
	clear();
}

void LobbyPage::addRoom(RoomIdInfos room)
{
	std::stringstream	ss;

	ss << room.second.second;
	_roomName.push_back(room.second.first + " : " + ss.str() + " players");
	_room.push_back(room);
	std::cout << "Room size = " << _room.size() << std::endl;
}

bool LobbyPage::init()
{
  std::vector<std::string>	test;

  initButton(70, 10, 60, Rect(_windowSize.first / 2 - 155 - _windowSize.first / 4, 900, 90, 310), "BACK", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::HOME);
  initButton(20, 10, 60, Rect(_windowSize.first / 2 - 155 + _windowSize.first / 4, 900, 90, 310), "CREATE", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::CREATEROOM);
	if (_room.size())
	  initDecor(Rect(_windowSize.first / 2 + 245, 753, 40, 200), "/res/img/buttonRoom.png");
  initListBox(Rect(_windowSize.first / 2 - 450, 450, 300, 900), "/res/fonts/Space.ttf", "/res/img/buttonRoom.png", "/res/img/buttonRoomOver.png", _roomName);
  return (true);
}

void LobbyPage::clear()
{
	_room.clear();
	_roomName.clear();
	clearGUIElement(_buttons);
	clearGUIElement(_guiElement);
}

bool LobbyPage::launch()
{
	return (true);
}

void LobbyPage::draw()
{
	_graph->setBackground(_backgroundSprite, 1.0f, 1.1f);
	_graph->drawText("Hen Type", _windowSize.first / 2 - 250, 100, 90, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
	drawGUIElement(_buttons);
	drawGUIElement(_guiElement);
}

RoomIdInfos		LobbyPage::getSelectedRoom() const
{
	std::vector<AGUIElement*>::const_iterator		it;

	it = _guiElement.begin();
	while (it != _guiElement.end())
	{
		if ((*it)->getTypeName() == "ListBox")
		{
			ListBox		*list;

			list = static_cast<ListBox* >(*it);
			if (list->getSelectedID() >= 0)
				return (_room.at(list->getSelectedID()));
		}
		++it;
	}
	std::pair<std::string, int> res("", -84);
	return (std::pair<int, std::pair<std::string, int>>(-84, res));
}

IPage::PAGE LobbyPage::event()
{
	IPage::PAGE		page;

	hoverEvent(_buttons);
	page = clickEvent(_buttons);
	clickEvent(_guiElement);
	if (page != IPage::NONE)
		_soundManager->play(_clickSound);
	return (page);
}

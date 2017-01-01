#include "InsideRoomPage.hh"


InsideRoomPage::InsideRoomPage(IGraphManager *graph, IEventManager *event, const PathFileManager &fileManager, ISoundManager *soundManager) : APage(graph, event, fileManager, soundManager)
{
	_backgroundSprite = _fileManager.getRoot() + "/res/img/background_menu2.jpg";
	_clickSound.setDuration(-1);
	_clickSound.setFilePath(_fileManager.getRoot() + "/res/sounds/buttonClick.wav");
	_pageType = IPage::INSIDEROOM;
	_roomName = "Room";
}

InsideRoomPage::~InsideRoomPage()
{
	clear();
}

bool InsideRoomPage::init()
{
	std::vector<std::pair<std::string, bool> >::iterator			it;
	int																i;

	i = 1;
	it = _playerList.begin();
	initButton(25, 5, 60, Rect(_windowSize.first / 2 - 155 + _windowSize.first / 4, 900, 90, 310), "LAUNCH", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::GAME);
	initButton(70, 5, 60, Rect(_windowSize.first / 2 - 155 - _windowSize.first / 4, 900, 90, 310), "BACK", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::PLAY);
	initDecor(Rect(_windowSize.first / 2 - 250, 150, 50, 500), "/res/img/bordureHaut.png");
	initDecor(Rect(_windowSize.first / 2 - 250, _windowSize.second - 400, 50, 500), "/res/img/bordureBas.png");
	while (it != _playerList.end())
	{
		initButton(20, 5, 30, Rect(_windowSize.first / 2 - 150, 130 + 80 * i, 50, 280), it->first, "/res/img/buttonRoom.png", "/res/img/buttonRoom.png", "/res/fonts/Space.ttf");
		if (!it->second)
			initDecor(Rect(_windowSize.first / 2 + 150, 130 + 80 * i, 50, 50), "/res/img/coche.png", Color(-1, -1, -1));
		else
			initDecor(Rect(_windowSize.first / 2 + 150, 130 + 80 * i, 50, 50), "/res/img/cocheRempli.png", Color(-1, -1, -1));
		++it;
		i++;
	}
	t1 = std::chrono::high_resolution_clock::now();
	return (true);
}

void InsideRoomPage::clear()
{
	clearGUIElement(_buttons);
	clearGUIElement(_guiElement);
	_playerList.clear();
}

bool InsideRoomPage::launch()
{
	return (true);
}

void InsideRoomPage::draw()
{
	_graph->setBackground(_backgroundSprite, 1.0f, 1.1f);
	_graph->drawText(_roomName, _windowSize.first / 2 - 200, 0, 90, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Space.ttf");
	drawGUIElement(_buttons);
	drawGUIElement(_guiElement);
}

IPage::PAGE InsideRoomPage::event()
{
	IPage::PAGE		page;

	hoverEvent(_buttons);
	page = clickEvent(_buttons);
	if (page != IPage::NONE)
		_soundManager->play(_clickSound);
	return (page);
}

void InsideRoomPage::setRoomName(const std::string & roomName)
{
	_roomName = roomName;
}

void InsideRoomPage::addPlayer(const std::string & name, const bool status)
{
	_playerList.push_back(std::pair<std::string, bool>(name, status));
}

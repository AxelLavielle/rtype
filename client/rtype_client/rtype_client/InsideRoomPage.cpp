#include "InsideRoomPage.hh"


InsideRoomPage::InsideRoomPage(IGraphManager *graph, IEventManager *event, const PathFileManager &fileManager, ISoundManager *soundManager) : APage(graph, event, fileManager, soundManager)
{
	_backgroundSprite = _fileManager.getRoot() + "/res/img/background_menu2.jpg";
	_clickSound.setDuration(-1);
	_clickSound.setFilePath(_fileManager.getRoot() + "/res/sounds/buttonClick.wav");
	_roomName = "";
	_pageType = IPage::INSIDEROOM;

	//Temporaire
	_playerList.insert(std::pair<std::string, bool>("PLAYER 1", false));
	_playerList.insert(std::pair<std::string, bool>("PLAYER 2", false));
	_playerList.insert(std::pair<std::string, bool>("PLAYER 3", true));
	_playerList.insert(std::pair<std::string, bool>("PLAYER 4", false));
	_roomName = "ROOM NAME";
	//
}

InsideRoomPage::~InsideRoomPage()
{
	clear();
}

bool InsideRoomPage::init()
{
	std::map<std::string, bool>::iterator			it;
	int												i;

	i = 1;
	it = _playerList.begin();
	initButton(25, 5, 60, Rect(_windowSize.first - 320, _windowSize.second - 100, 90, 310), "LAUNCH", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::GAME);
	initButton(70, 5, 60, Rect(10, _windowSize.second - 100, 90, 310), "BACK", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::PLAY);
	initDecor(Rect(290, 150, 50, 500), "/res/img/bordureHaut.png");
	initDecor(Rect(290, _windowSize.second - 200, 50, 500), "/res/img/bordureBas.png");
	while (it != _playerList.end())
	{
		initButton(20, 5, 30, Rect(_windowSize.first / 2 - 150, 130 + 80 * i, 50, 280), it->first, "/res/img/buttonRoom.png", "/res/img/buttonRoom.png", "/res/fonts/Space.ttf");
		if (!it->second)
			initDecor(Rect(_windowSize.first - 400, 130 + 80 * i, 50, 50), "/res/img/coche.png", Color(-1, -1, -1));
		else
			initDecor(Rect(_windowSize.first - 400, 130 + 80 * i, 50, 50), "/res/img/cocheRempli.png", Color(-1, -1, -1));
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
}

bool InsideRoomPage::launch()
{
	//Not implemented
	return (true);
}

void InsideRoomPage::draw()
{
	_graph->setBackground(_backgroundSprite, 0.6f, 0.7f);
	_graph->drawText(_roomName, 300, 0, 90, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
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
	_playerList.insert(std::pair<std::string, bool>(name, status));
}

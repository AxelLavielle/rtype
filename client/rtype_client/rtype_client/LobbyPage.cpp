#include "LobbyPage.hh"


LobbyPage::LobbyPage(IGraphManager *graph, IEventManager *event, const PathFileManager &fileManager, ISoundManager *soundManager) : APage(graph, event, fileManager, soundManager)
{
	_backgroundSprite = _fileManager.getRoot() + "/res/img/background_menu2.jpg";
	_clickSound.setDuration(-1);
	_clickSound.setFilePath(_fileManager.getRoot() + "/res/sounds/buttonClick.wav");
}

LobbyPage::~LobbyPage()
{
	clear();
}

bool LobbyPage::init()
{
  std::vector<std::string>	test;

  initButton(70, 10, 60, Rect(20, 600, 90, 310), "BACK", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::HOME);
  initButton(50, 10, 60, Rect(750, 600, 90, 310), "JOIN", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::ROOMLIST);
  initButton(20, 10, 60, Rect(387, 600, 90, 310), "CREATE", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::INSIDEROOM);
  test.push_back("ELEMENT 1");
  test.push_back("ELEMENT NEXT");
  test.push_back("ELEMENT NEXT");
  test.push_back("ELEMENT NEXT");
  test.push_back("ELEMENT NEXT");
  test.push_back("ELEMENT NEXT");
  test.push_back("ELEMENT NEXT");
  test.push_back("ELEMENT NEXT NEXT");
  test.push_back("ELEMENT NEXT NEXT");
  test.push_back("ELEMENT NEXT NEXT");
  test.push_back("ELEMENT NEXT NEXT");
  test.push_back("ELEMENT NEXT NEXT");
  test.push_back("ELEMENT NEXT NEXT");
  test.push_back("ELEMENT NEXT NEXT");
  test.push_back("ELEMENT NEXT NEXT NEXT");
  initListBox(Rect(100, 250, 300, 900), "/res/fonts/Aerospace.ttf", "/res/img/buttonRoom.png", "/res/img/buttonRoomOver.png", test);
  return (true);
}

void LobbyPage::clear()
{
	clearGUIElement(_buttons);
	clearGUIElement(_guiElement);
}

bool LobbyPage::launch()
{
	//Not implemented
	return (true);
}

void LobbyPage::draw()
{
	_graph->setBackground(_backgroundSprite, 0.6f, 0.7f);
	_graph->drawText("Hen Type", 300, 0, 90, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
	drawGUIElement(_buttons);
	drawGUIElement(_guiElement);
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

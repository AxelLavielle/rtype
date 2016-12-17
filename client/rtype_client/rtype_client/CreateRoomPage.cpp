#include "CreateRoomPage.hh"


CreateRoomPage::CreateRoomPage(IGraphManager * graph, IEventManager * event, const PathFileManager & fileManager, ISoundManager * soundManager)
{
	_clickSound.setDuration(-1);
	_clickSound.setFilePath(_fileManager.getRoot() + "/res/sounds/buttonClick.wav");
}

CreateRoomPage::~CreateRoomPage()
{
	clear();
}

bool CreateRoomPage::init()
{
	return (true);
}

void CreateRoomPage::clear()
{
	initButton(25, 10, 60, Rect(750, 600, 90, 310), "PLAY", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::GAME);
	initButton(25, 10, 60, Rect(750, 600, 90, 310), "BACK", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::PLAY);
	//initInputBox(Rect(200, 300, 30, 700));
	clearGUIElement(_buttons);
	clearGUIElement(_guiElement);
}

bool CreateRoomPage::launch()
{
	return (true);
}

void CreateRoomPage::draw()
{
	_graph->drawText("Hen Type", 300, 0, 90, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
	drawGUIElement(_buttons);
	drawGUIElement(_guiElement);
}

IPage::PAGE CreateRoomPage::event()
{
	IPage::PAGE		page;

	hoverEvent(_buttons);
	page = clickEvent(_buttons);
	if (page != IPage::NONE)
		_soundManager->play(_clickSound);
	return (page);
}

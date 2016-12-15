#include "InsideRoomPage.hh"


InsideRoomPage::InsideRoomPage(IGraphManager *graph, IEventManager *event, const PathFileManager &fileManager, ISoundManager *soundManager) : APage(graph, event, fileManager, soundManager)
{
	_backgroundSprite = _fileManager.getRoot() + "/res/img/background_menu2.jpg";
	_clickSound.setDuration(-1);
	_clickSound.setFilePath(_fileManager.getRoot() + "/res/sounds/buttonClick.wav");
}

InsideRoomPage::~InsideRoomPage()
{
	clear();
}

bool InsideRoomPage::init()
{
	// initButton(70, 10, 60, Rect(380, 200, 90, 310), "PLAY", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::PLAY);
	// initButton(20, 10, 60, Rect(380, 380, 90, 310), "OPTION", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::SETTINGS);
	// initButton(70, 10, 60, Rect(380, 550, 90, 310), "QUIT", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::QUIT);
	initDecor(Rect(290, 150, 50, 500), "/res/img/bordureHaut.png");
	initDecor(Rect(290, 650, 50, 500), "/res/img/bordureBas.png");
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
	_graph->drawText("Hen Type", 300, 0, 90, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
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

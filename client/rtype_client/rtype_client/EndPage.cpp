#include "EndPage.hh"

EndPage::EndPage(IGraphManager *graph, IEventManager *event, const PathFileManager &fileManager, ISoundManager *soundManager) : APage(graph, event, fileManager, soundManager)
{
	_backgroundSprite = _fileManager.getRoot() + "/res/img/background_menu3.jpg";
	_clickSound.setDuration(-1);
	_clickSound.setFilePath(_fileManager.getRoot() + "/res/sounds/buttonClick.wav");
}

EndPage::~EndPage()
{
}

bool			EndPage::init()
{
	initButton(70, 10, 60, Rect(380, 550, 90, 310), "RETURN TO MENU", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::HOME);
	initButton(70, 10, 60, Rect(380, 550, 90, 310), "QUIT", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::QUIT);
	return (true);
}

void			EndPage::clear()
{

}

bool			EndPage::launch()
{
	return (true);
}

void			EndPage::draw()
{

}

IPage::PAGE		EndPage::event()
{
	return (IPage::ENDGAME);
}
#include "EndGamePage.hh"

EndGamePage::EndGamePage(IGraphManager *graph, IEventManager *event, const PathFileManager &fileManager, ISoundManager *soundManager) : APage(graph, event, fileManager, soundManager)
{
	_backgroundSprite = _fileManager.getRoot() + "/res/img/background_menu3.jpg";
	_clickSound.setDuration(-1);
	_clickSound.setFilePath(_fileManager.getRoot() + "/res/sounds/buttonClick.wav");
}

EndGamePage::~EndGamePage()
{
}

bool			EndGamePage::init()
{
	initButton(70, 10, 60, Rect(380, 550, 90, 310), "RETURN TO MENU", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::HOME);
	initButton(70, 10, 60, Rect(380, 550, 90, 310), "QUIT", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::QUIT);
	return (true);
}

void			EndGamePage::clear()
{

}

bool			EndGamePage::launch()
{
	return (true);
}

void			EndGamePage::draw()
{

}

IPage::PAGE		EndGamePage::event()
{
	return (IPage::ENDGAME);
}

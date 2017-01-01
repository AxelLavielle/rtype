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
	initButton(70, 5, 30, Rect(_windowSize.first / 2 - 155 - _windowSize.first / 4, 900, 90, 310), "RETURN\nTO MENU", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Space.ttf", IPage::HOME);
	initButton(70, 5, 60, Rect(_windowSize.first / 2 - 155 + _windowSize.first / 4, 900, 90, 310), "QUIT", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Space.ttf", IPage::QUIT);
	return (true);
}

void			EndGamePage::clear()
{
	clearGUIElement(_buttons);
	clearGUIElement(_guiElement);
}

bool			EndGamePage::launch()
{
	return (true);
}

void			EndGamePage::draw()
{
	std::vector< std::pair<std::string, int>>::iterator	it = _scores.begin();
	int			y = 470;

	_graph->setBackground(_backgroundSprite, 1.0f, 1.1f);
	initDecor(Rect(_windowSize.first / 2 - 250, 400, 50, 500), "/res/img/buttonRoom.png");
	initDecor(Rect(_windowSize.first / 2 - 250, 460, 250, 500), "/res/img/buttonRoom.png");
	drawGUIElement(_buttons);
	drawGUIElement(_guiElement);
	_graph->drawText("GAME OVER", _windowSize.first / 2 - 300, 100, 90, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Space.ttf");
	_graph->drawText("Score : ", _windowSize.first / 2 - 230, 400, 30, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Space.ttf");
	while (it != _scores.end())
	{
		_graph->drawText(it->first + " : " + std::to_string(it->second), _windowSize.first / 2 - 230, y, 25, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Space.ttf");
		y += 60;
		it++;
	}
	_graph->drawText("Destroyed waves : " + std::to_string(_destroyedWaves), _windowSize.first / 2 - 230, 800, 30, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Space.ttf");
	_graph->setMouseCursorVisible(true);
}

IPage::PAGE		EndGamePage::event()
{
	IPage::PAGE		page;

	hoverEvent(_buttons);
	page = clickEvent(_buttons);
	if (page != IPage::NONE)
		_soundManager->play(_clickSound);
	return (page);
}

void			EndGamePage::addPlayer(const std::string &name, const int score)
{
	_scores.push_back(std::make_pair(name, score));
}

void			EndGamePage::setWave(const int wave)
{
	_destroyedWaves = wave;
}
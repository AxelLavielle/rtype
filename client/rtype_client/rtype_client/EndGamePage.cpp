#include "EndGamePage.hh"

EndGamePage::EndGamePage(IGraphManager *graph, IEventManager *event, const PathFileManager &fileManager, ISoundManager *soundManager) : APage(graph, event, fileManager, soundManager)
{
	_backgroundSprite = _fileManager.getRoot() + "/res/img/background_menu3.jpg";
	_clickSound.setDuration(-1);
	_clickSound.setFilePath(_fileManager.getRoot() + "/res/sounds/buttonClick.wav");
	_scores.push_back(std::make_pair<std::string, int>("Kebabaman", 684684));
	_scores.push_back(std::make_pair<std::string, int>("hmardingdingdong", 453738));
	_scores.push_back(std::make_pair<std::string, int>("hihijaiungroszizi", 98384));
	_scores.push_back(std::make_pair<std::string, int>("alexislepd", 12));
}

EndGamePage::~EndGamePage()
{
}

bool			EndGamePage::init()
{
	initButton(70, 5, 30, Rect(180, 550, 90, 310), "RETURN\nTO MENU", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::HOME);
	initButton(70, 5, 60, Rect(580, 550, 90, 310), "QUIT", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::QUIT);
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
	int			y = 270;

	_graph->setBackground(_backgroundSprite, 0.6f, 0.7f);
	initDecor(Rect(290, 200, 50, 500), "/res/img/buttonRoom.png");
	initDecor(Rect(290, 260, 190, 500), "/res/img/buttonRoom.png");
	drawGUIElement(_buttons);
	drawGUIElement(_guiElement);
	_graph->drawText("GAME OVER", 230, 0, 90, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
	_graph->drawText("Score : ", 300, 200, 30, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
	while (it != _scores.end())
	{
		_graph->drawText(it->first + " : " + std::to_string(it->second), 300, y, 25, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
		y += 40;
		it++;
	}
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

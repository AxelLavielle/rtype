#include "HomePage.hh"

HomePage::HomePage(IGraphManager *graph, IEventManager *event, const PathFileManager &fileManager, ISoundManager *soundManager) : APage(graph, event, fileManager, soundManager)
{
	_animInc = 0;
	_backgroundSprite = _fileManager.getRoot() + "/res/img/background_menu3.jpg";
	_clickSound.setDuration(-1);
	_clickSound.setFilePath(_fileManager.getRoot() + "/res/sounds/buttonClick.wav");
}


HomePage::~HomePage()
{
	clear();
}

bool HomePage::init()
{
	initButton(70, 10, 60, Rect(380, 200, 90, 310), "PLAY", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::PLAY);
	initButton(20, 10, 60, Rect(380, 380, 90, 310), "OPTION", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::SETTINGS);
	initButton(70, 10, 60, Rect(380, 550, 90, 310), "QUIT", "/res/img/button.png", "/res/img/buttonOver.png", "/res/fonts/Aerospace.ttf", IPage::ENDGAME);
	initDecor(Rect(290, 150, 50, 500), "/res/img/bordureHaut.png");
	initDecor(Rect(290, 650, 50, 500), "/res/img/bordureBas.png");
	t1 = std::chrono::high_resolution_clock::now();
	return (true);
}

void HomePage::clear()
{
	clearGUIElement(_buttons);
	clearGUIElement(_guiElement);
}

bool HomePage::launch()
{
	return (true);
}

void HomePage::firstAnim()
{
	int									i;
	Rect								tmp;
	std::chrono::high_resolution_clock::time_point        t2;
	std::map<IPage::PAGE, AGUIElement* >::iterator			it;

	i = 1;
	it = _buttons.begin();
	while (it != _buttons.end())
	{
		if (_animInc < 190 * i && i <= 3)
		{
			t2 = std::chrono::high_resolution_clock::now();
			_animDuration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
			if (_animDuration > ANIMDURATION)
			{
				t1 = std::chrono::high_resolution_clock::now();
				_animInc++;
			}
			tmp = it->second->getPos();
			it->second->setPos(Rect(tmp.getX(), _animInc, tmp.getHeight(), tmp.getWidth()));
		}
		++it;
		i++;
	}
}

void HomePage::draw()
{
	firstAnim();
	_graph->setBackground(_backgroundSprite, 0.6f, 0.7f);
	_graph->drawText("Hen Type", 300, 0, 90, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Aerospace.ttf");
	drawGUIElement(_buttons);
	drawGUIElement(_guiElement);
}

IPage::PAGE HomePage::event()
{
	IPage::PAGE		page;

	hoverEvent(_buttons);
	page = clickEvent(_buttons);
	if (page != IPage::NONE)
		_soundManager->play(_clickSound);
	return (page);
}

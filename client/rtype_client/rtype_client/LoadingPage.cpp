#include "LoadingPage.hh"

LoadingPage::LoadingPage(IGraphManager *graph, IEventManager *event, const PathFileManager &fileManager, ISoundManager *soundManager) : APage(graph, event, fileManager, soundManager)
{
}

LoadingPage::~LoadingPage()
{
}

bool LoadingPage::init()
{
	initDecor(Rect(_windowSize.first / 2 - 200, _windowSize.second / 2 - 100, 200, 400), "/res/img/buttonRoom.png");
	initButton(70, 5, 60, Rect(_windowSize.first / 2 - 150, _windowSize.second / 2 - 60, 30, 70), "", "/res/img/spaceShip10.png", "/res/img/spaceShip10.png", "/res/fonts/Space.ttf");
	initButton(70, 5, 60, Rect(_windowSize.first / 2 - 150, _windowSize.second / 2 + 30, 30, 70), "", "/res/img/spaceShip10.png", "/res/img/spaceShip10.png", "/res/fonts/Space.ttf");
	return (true);
}

void LoadingPage::clear()
{
	clearGUIElement(_guiElement);
}

bool LoadingPage::launch()
{
	return (true);
}

void	LoadingPage::loadingAnim()
{
	int														i;
	Rect													tmp;
	std::chrono::high_resolution_clock::time_point			t2;
	std::vector<AGUIElement* >::iterator					it;

	i = 1;
	it = _guiElement.begin();
	while (it != _guiElement.end())
	{
		if (_animInc < 700 * i && i <= 2)
		{
			t2 = std::chrono::high_resolution_clock::now();
			_animDuration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
			if (_animDuration > ANIMDURATION)
			{
				t1 = std::chrono::high_resolution_clock::now();
				_animInc += 5;
			}
			tmp = (*it)->getPos();
			std::cout << (*it)->getTypeName() << std::endl;
			if ((*it)->getTypeName() == "Button")
				(*it)->setPos(Rect(_animInc, tmp.getY(), tmp.getHeight(), tmp.getWidth()));
		}
		++it;
		i++;
	}
}

void LoadingPage::draw()
{
	loadingAnim();
	drawGUIElement(_guiElement);
	drawGUIElement(_buttons);
	_graph->drawText("Loading...", _windowSize.first / 2 - 80, _windowSize.second / 2 - 20, 30, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Space.ttf");
}

IPage::PAGE LoadingPage::event()
{
	IPage::PAGE		page;

	hoverEvent(_buttons);
	page = clickEvent(_buttons);
	return (page);
}
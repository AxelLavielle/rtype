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
	//initButton(70, 5, 60, Rect(_windowSize.first / 2 - 150, _windowSize.second / 2 - 60, 30, 70), "", "/res/img/spaceShip10.png", "/res/img/spaceShip10.png", "/res/fonts/Space.ttf");
	//initButton(70, 5, 60, Rect(_windowSize.first / 2 - 150, _windowSize.second / 2 + 30, 30, 70), "", "/res/img/spaceShip10.png", "/res/img/spaceShip10.png", "/res/fonts/Space.ttf");
	_animInc = _windowSize.first / 2 - 200;
	_animInc2 = _windowSize.first / 2 - 35;
//	_animInc3 = _windowSize.first / 2 - 200;
//	_animInc4 = _windowSize.first / 2;
	//_imgW = 70;
	//_img2W = 70;
//	_img3W = 0;
//	_img4W = 0;
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

	i = 0;
	t2 = std::chrono::high_resolution_clock::now();
	_animDuration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	if (_animDuration > ANIMDURATION_L)
	{
		t1 = std::chrono::high_resolution_clock::now();
		if (_animInc > _windowSize.first / 2 - 200 + 325)
			_animInc = _windowSize.first / 2 - 200;
		if (_animInc2 > _windowSize.first / 2 - 200 + 325)
			_animInc2 = _windowSize.first / 2 - 200;
		_animInc += 1;
		_animInc2 += 1;
	}
	i++;
}

void LoadingPage::draw()
{
	loadingAnim();
	drawGUIElement(_guiElement);
	drawGUIElement(_buttons);
	_graph->drawText("Loading...", _windowSize.first / 2 - 80, _windowSize.second / 2 - 20, 30, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Space.ttf");
	_graph->drawRectangle(_fileManager.getRoot() + "/res/img/spaceShip10.png", Rect(_animInc, _windowSize.second / 2 - 60, 0, 0), Rect(0, 0, 0, 0), Rect(0, 0, 30, 70));
	_graph->drawRectangle(_fileManager.getRoot() + "/res/img/spaceShip10.png", Rect(_animInc2, _windowSize.second / 2 + 30, 0, 0), Rect(0, 0, 0, 0), Rect(0, 0, 30, 70));
}

IPage::PAGE LoadingPage::event()
{
	IPage::PAGE		page;

	hoverEvent(_buttons);
	page = clickEvent(_buttons);
	return (page);
}
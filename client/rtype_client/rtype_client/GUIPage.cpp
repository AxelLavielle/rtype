#include "GUIPage.hh"



GUIPage::GUIPage(IGraphManager *graph, IEventManager *event, const PathFileManager &fileManager, ISoundManager *soundManager) : APage(graph, event, fileManager, soundManager)
{
}


GUIPage::~GUIPage()
{
	clear();
}

bool GUIPage::init()
{
	initDecor(Rect(0, 0, 100, _windowSize.first), "/res/img/barreJeu.png");
	initDecor(Rect(0, _windowSize.second - 150, 150, _windowSize.first), "/res/img/barreJeu.png");
	initDecor(Rect(20, _windowSize.second - 130, 50, 50), "/res/img/iconeDefense.png");
	initDecor(Rect(20, _windowSize.second - 75, 50, 50), "/res/img/iconeVie.png");
	initDecor(Rect(_windowSize.first - 250, _windowSize.second - 130, 100, 200), "/res/img/fondCadre.png");
	initDecor(Rect(400, _windowSize.second - 140, 130, 20), "/res/img/splitBar.png");
	initDecor(Rect(440, _windowSize.second - 95, 30, 70), "/res/img/spaceShip10.png", Color(0, 0, 0));
	initButton(70, 10, 60, Rect(0, 0, 90, 310), "HEN TYPE", "", "", "/res/fonts/Aerospace.ttf", IPage::NONE);
	_hp = 4;
	_def = 4;
	_nbPlayers = 1;
	_score = 456789;
	_mode = "Facile";
	_playerName = "Jean-Kebab";
	return (true);
}

void GUIPage::clear()
{
	clearGUIElement(_guiElement);
}

bool GUIPage::launch()
{
	return (true);
}

void	GUIPage::titleAnimation()
{
	int									i;
	Rect								tmp;
	std::chrono::high_resolution_clock::time_point        t2;
	std::map<IPage::PAGE, AGUIElement* >::iterator			it;

	i = 1;
	it = _buttons.begin();
	while (it != _buttons.end())
	{
		std::cout << i << std::endl;
		if (_animInc < 700 * i && i <= 1)
		{
			t2 = std::chrono::high_resolution_clock::now();
			_animDuration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
			if (_animDuration > ANIMDURATION)
			{
				t1 = std::chrono::high_resolution_clock::now();
				_animInc+=5;
			}
			tmp = it->second->getPos();
			it->second->setPos(Rect(_animInc, tmp.getY(), tmp.getHeight(), tmp.getWidth()));
		}
		++it;
		i++;
	}
}

void GUIPage::draw()
{
	titleAnimation();
	initDecor(Rect(80, _windowSize.second - 130, 50, 300), "/res/img/barreDefense" + std::to_string(_def) + ".png");
	initDecor(Rect(80, _windowSize.second - 75, 50, 300), "/res/img/barreVie" + std::to_string(_hp) + ".png");
	drawGUIElement(_guiElement);
	drawGUIElement(_buttons);
	_graph->drawText("Nb joueur : " + std::to_string(_nbPlayers), _windowSize.first - 230, _windowSize.second - 110, 19, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Space.ttf");
	_graph->drawText("Mode : " + _mode, _windowSize.first - 230, _windowSize.second - 70, 19, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Space.ttf");
	_graph->drawText("Score : " + std::to_string(_score), _windowSize.first - 600, _windowSize.second - 100, 30, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Space.ttf");
	_graph->drawText(_playerName, 530, _windowSize.second - 100, 30, Color(135, 206, 250, 255), _fileManager.getRoot() + "/res/fonts/Space.ttf");
}

IPage::PAGE GUIPage::event()
{
	IPage::PAGE		page;

	hoverEvent(_buttons);
	page = clickEvent(_buttons);
	return (page);
}

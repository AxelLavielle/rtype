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
	initDecor(Rect(80, _windowSize.second - 130, 50, 150), "/res/img/barreVie4.png");
	initDecor(Rect(80, _windowSize.second - 75, 50, 150), "/res/img/barreDefense4.png");
	initDecor(Rect(20, _windowSize.second - 130, 50, 50), "/res/img/iconeDefense.png");
	initDecor(Rect(20, _windowSize.second - 75, 50, 50), "/res/img/iconeVie.png");
	initDecor(Rect(_windowSize.first - 250, _windowSize.second - 130, 100, 200), "/res/img/fondCadre.png");
	initDecor(Rect(250, _windowSize.second - 140, 130, 20), "/res/img/splitBar.png");
	initDecor(Rect(300, _windowSize.second - 140, 30, 70), "/res/img/spaceShip10.png", Color(0, 0, 0));
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

void GUIPage::draw()
{
	drawGUIElement(_guiElement);
	_graph->drawText("HEN TYPE", _windowSize.first / 2 - 220, 0, 80, Color(135, 206, 250, 255), "../../res/fonts/Aerospace.ttf");
	_graph->drawText("Nb joueur", _windowSize.first - 190, _windowSize.second - 110, 19, Color(135, 206, 250, 255), "../../res/fonts/Aerospace.ttf");
	_graph->drawText("DIFFICULTE", _windowSize.first - 190, _windowSize.second - 70, 19, Color(135, 206, 250, 255), "../../res/fonts/Aerospace.ttf");
	_graph->drawText("SCORE : 0", _windowSize.first - 600, _windowSize.second - 100, 30, Color(135, 206, 250, 255), "../../res/fonts/OpenSans-Regular.ttf");
}

IPage::PAGE GUIPage::event()
{
	IPage::PAGE		page;

	hoverEvent(_buttons);
	page = clickEvent(_buttons);
	return (page);
}

#include "Game.hh"



Game::Game()
{
}


Game::~Game()
{
	std::vector<AGUIElement* >::iterator		it;

	it = _guiElement.begin();
	while (it != _guiElement.end())
	{
		delete (*it);
		++it;
	}
	_guiElement.clear();
}

void Game::createUI()
{
	std::pair<int, int>		size;
	size = _graph->getScreenSize();
	std::cout << "first = " << size.first << " second = " << size.second << std::endl;
	RectDecor *topUI = new RectDecor(_graph, _event, Rect(0, 0, 100, size.first));
	RectDecor	*bottomUI = new RectDecor(_graph, _event, Rect(0, size.second - 100, 100, size.first));
	RectDecor	*lifeBar = new RectDecor(_graph, _event, Rect(50, size.second - 10, 50, 150));
	RectDecor	*powerBar = new RectDecor(_graph, _event, Rect(50, size.second - 60, 50, 150));


	topUI->setBackgroundSprite("../../res/img/button.jpg");
	bottomUI->setBackgroundSprite("../../res/img/button.jpg");
	lifeBar->setBackgroundSprite("../../res/img/barreVie4.png");
	powerBar->setBackgroundSprite("../../res/img/barreDefense4.png");
	
	_guiElement.push_back(topUI);
	_guiElement.push_back(bottomUI);
	_guiElement.push_back(lifeBar);
	_guiElement.push_back(powerBar);
}

#include <iostream>

void Game::drawUi()
{
	std::vector<AGUIElement* >::iterator		it;

	it = _guiElement.begin();
	while (it != _guiElement.end())
	{
		(*it)->draw();
		++it;
	}
}

int Game::launch()
{
	std::chrono::high_resolution_clock::time_point      t1;
	std::chrono::high_resolution_clock::time_point	    t2;
	double												duration;
	int													i;
	bool												first = true;

	i = 100;
	_graph->setFullScreen(true);
	t1 = std::chrono::high_resolution_clock::now();
	createUI();
	while (_graph->isWindowOpen())
	{
		while (_event->refresh())
		{
			//if ((ret = buttonEvent()) == 1)
			//	return (true);
			//else if (ret == 2)
			//	return (false);
			if (_event->getCloseEvent() || _event->getKeyStroke() == "ECHAP")
				return (1);
		}
		_graph->clearWindow();
		t2 = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
		_graph->setBackground("../../res/img/stars_background.jpg", -1, -1);
		if (first || duration >= 10000)
		{
			i += 10;
			if (i >= 1000)
				i = 0;
			first = false;
			t1 = std::chrono::high_resolution_clock::now();
		}
		_graph->drawRectangle(Color(255, 255, 255), Rect(i, 300, 50, 50));
		drawUi();
		_graph->refresh();
	}
	return (0);
}

void Game::setGraph(IGraphManager * graph)
{
	_graph = graph;
}

void Game::setEvent(IEventManager * event)
{
	_event = event;
}

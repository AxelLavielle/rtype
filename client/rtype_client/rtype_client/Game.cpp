#include "Game.hh"



Game::Game()
{
}


Game::~Game()
{
}
#include <iostream>
int Game::launch()
{
	std::chrono::high_resolution_clock::time_point        t1;
	std::chrono::high_resolution_clock::time_point	     t2;
	double												duration;
	int													i;
	bool												first = true;

	i = 100;
//	_graph->setFullScreen(true);
	t1 = std::chrono::high_resolution_clock::now();
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
		std::cout << "i = " << i << std::endl;
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

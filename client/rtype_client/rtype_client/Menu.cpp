#include "Menu.hh"



Menu::Menu()
{
}


Menu::~Menu()
{
}

bool Menu::init()
{
	return (true);
}

bool Menu::launch()
{
	_graph->setBackground("../../res/img/background_menu2.jpg");
	while (_graph->isWindowOpen())
	{
		while (_event->refresh())
		{
			if (_event->getCloseEvent() || _event->getKeyStroke() == "ECHAP")
				_graph->close();
		}
		_graph->refresh();
	}
	return (true);
}

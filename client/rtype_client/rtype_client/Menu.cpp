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

void Menu::initButton()
{
	Button		play(_graph, _event, Rect(380, 150, 90, 310), "PLAY");
	Button		quit(_graph, _event, Rect(380, 500, 90, 310), "QUIT");

	play.setTextPos(70, 10);
	play.setTextSize(60);
	quit.setTextPos(70, 10);
	quit.setTextSize(60);
	_buttons.push_back(play);
	_buttons.push_back(quit);
}

void Menu::drawButton()
{
	std::vector<Button>::iterator		it;

	it = _buttons.begin();
	while (it != _buttons.end())
	{
		(*it).draw();
		++it;
	}
}

void Menu::ButtonEvent()
{
	std::vector<Button>::iterator		it;

	it = _buttons.begin();
	while (it != _buttons.end())
	{
		(*it).over();
		++it;
	}
}

bool Menu::launch()
{
	initButton();
	while (_graph->isWindowOpen())
	{
		while (_event->refresh())
		{
			if (_buttons[0].click())
				return (true);
			if (_buttons[1].click() || _event->getCloseEvent() || _event->getKeyStroke() == "ECHAP")
				_graph->close();
		}
		_graph->clearWindow();
		_graph->setBackground("../../res/img/background_menu2.jpg");
		drawButton();
		_graph->drawText("Hen Type", 350, 0, 70, Color(224, 224, 224, 255), "../../res/fonts/Aerospace.ttf");
		_graph->refresh();
	}
	return (false);
}

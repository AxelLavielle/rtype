#include "Menu.hh"

Menu::Menu()
{
	_pagenb = PAGE::ACCEUIL;
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
	Button		quit(_graph, _event, Rect(380, 600, 90, 310), "QUIT");
	Button		option(_graph, _event, Rect(380, 380, 90, 310), "OPTION");

	_pagenb = PAGE::ACCEUIL;
	_buttons.clear();
	_listBox.clear();
	play.setTextPos(70, 10);
	play.setTextSize(60);
	quit.setTextPos(70, 10);
	quit.setTextSize(60);
	option.setTextPos(20, 10);
	option.setTextSize(60);
	_buttons.push_back(play);
	_buttons.push_back(quit);
	_buttons.push_back(option);
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

void Menu::drawListBox()
{
	std::vector<ListBox>::iterator		it;

	it = _listBox.begin();
	while (it != _listBox.end())
	{
		(*it).draw();
		++it;
	}
}

void Menu::roomList()
{
	Button						play(_graph, _event, Rect(750, 600, 90, 310), "JOIN");
	Button						quit(_graph, _event, Rect(20, 600, 90, 310), "BACK");
	std::vector<std::string>	elements;
	ListBox						list(_graph, _event, Rect(100, 250, 300, 900));


	elements.push_back("ELEMENT 1");
	elements.push_back("ELEMENT NEXT");
	list.setElements(elements);
	_buttons.clear();
	_listBox.clear();
	_pagenb = PAGE::ROOMLIST;
	play.setTextPos(70, 10);
	play.setTextSize(60);
	quit.setTextPos(70, 10);
	quit.setTextSize(60);
	_buttons.push_back(play);
	_buttons.push_back(quit);
	_listBox.push_back(list);
}

void Menu::createRoom()
{
	Button		play(_graph, _event, Rect(750, 600, 90, 310), "JOIN");
	Button		quit(_graph, _event, Rect(20, 600, 90, 310), "BACK");

	_buttons.clear();
	_listBox.clear();
	_pagenb = PAGE::ROOMCREATE;
	play.setTextPos(70, 10);
	play.setTextSize(60);
	quit.setTextPos(70, 10);
	quit.setTextSize(60);
	_buttons.push_back(play);
	_buttons.push_back(quit);
}

void Menu::settings()
{
	Button		play(_graph, _event, Rect(750, 600, 90, 310), "SAVE");
	Button		quit(_graph, _event, Rect(20, 600, 90, 310), "BACK");

	_buttons.clear();
	_listBox.clear();
	_pagenb = PAGE::SETTINGS;
	play.setTextPos(70, 10);
	play.setTextSize(60);
	quit.setTextPos(70, 10);
	quit.setTextSize(60);
	_buttons.push_back(play);
	_buttons.push_back(quit);
}

char Menu::buttonEvent() //A CORRIGER
{
	std::vector<Button>::iterator		it;

	it = _buttons.begin();
	while (it != _buttons.end())
	{
		(*it).over();
		++it;
	}
	if (_buttons[0].click())
	{
		if (_pagenb == PAGE::ACCEUIL)
			roomButton();
		else if (_pagenb == PAGE::PLAY)
			return (1); //Doit lancer le jeu
	}
	else if (_buttons[1].click())
	{
		if (_pagenb == PAGE::PLAY)
			initButton();
		else if (_pagenb == PAGE::ROOMLIST)
			roomButton();
		else if (_pagenb == PAGE::ROOMCREATE)
			roomButton();
		else if (_pagenb == PAGE::SETTINGS)
			initButton();
		else if (_pagenb == PAGE::ACCEUIL)
			return (2); //Doit quitter
	}
	else if (_pagenb == PAGE::PLAY && _buttons[3].click())
		createRoom();
	else if (_pagenb == PAGE::ACCEUIL && _buttons[2].click())
		settings();
	else if (_pagenb == PAGE::PLAY && _buttons[2].click())
		roomList();
	else if ((_buttons[1].click() && _pagenb == PAGE::ACCEUIL) || _event->getCloseEvent() || _event->getKeyStroke() == "ECHAP")
		_graph->close();
	return (0);
}

void Menu::roomButton()
{
	Button		play(_graph, _event, Rect(750, 600, 90, 310), "PLAY");
	Button		quit(_graph, _event, Rect(20, 600, 90, 310), "BACK");
	Button		join(_graph, _event, Rect(300, 380, 90, 500), "JOIN ROOM");
	Button		create(_graph, _event, Rect(300, 150, 90, 500), "CREATE ROOM");

	_pagenb = PAGE::PLAY;
	_buttons.clear();
	_listBox.clear();
	play.setTextPos(70, 10);
	play.setTextSize(60);
	quit.setTextPos(70, 10);
	quit.setTextSize(60);
	join.setTextPos(50, 10);
	join.setTextSize(60);
	create.setTextPos(20, 10);
	create.setTextSize(60);
	_buttons.push_back(play);
	_buttons.push_back(quit);
	_buttons.push_back(join);
	_buttons.push_back(create);
}

bool Menu::launch()
{
	char ret;
	initButton();
	while (_graph->isWindowOpen())
	{
		while (_event->refresh())
		{
			if ((ret = buttonEvent()) == 1)
				return (true);
			else if (ret == 2)
				return (false);
		}
		_graph->clearWindow();
		_graph->setBackground("../../res/img/background_menu2.jpg");
		drawButton();
		drawListBox();
		_graph->drawText("Hen Type", 300, 0, 90, Color(224, 224, 224, 255), "../../res/fonts/Aerospace.ttf");
		if (_pagenb == PAGE::ROOMLIST)
			_graph->drawText("Choice a room", 350, 150, 40, Color(224, 224, 224, 255), "../../res/fonts/Aerospace.ttf");
		_graph->refresh();
	}
	return (false);
}

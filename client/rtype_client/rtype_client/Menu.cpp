#include "AGUIElement.hh"
#include "Menu.hh"

Menu::Menu()
{
	_pagenb = PAGE::ACCEUIL;
	_animInc = 0;
	_first = true;
	_music.setDuration(-1);
	_music.setMusic(true);
	_music.setFilePath("../../res/sounds/opening.wav");
	_music.setLoop(true);
	_clickSound.setDuration(-1);
	_clickSound.setFilePath("../../res/sounds/buttonClick.wav");
	_soundManager.play(_music);	
	_fileManager.init();
	_funcPtr.insert(std::pair<PAGE, funcPtr>(PAGE::PLAY, &Menu::initButton));
	_funcPtr.insert(std::pair<PAGE, funcPtr>(PAGE::ROOMLIST, &Menu::roomButton));
	_funcPtr.insert(std::pair<PAGE, funcPtr>(PAGE::ROOMCREATE, &Menu::roomButton));
	_funcPtr.insert(std::pair<PAGE, funcPtr>(PAGE::SETTINGS, &Menu::initButton));
	_funcPtr.insert(std::pair<PAGE, funcPtr>(PAGE::ACCEUIL, &Menu::settings));
	std::cout << "HOME = " << _fileManager.getRoot() << std::endl;
}


Menu::~Menu()
{
}

bool Menu::init()
{
	return (true);
}

void Menu::clear()
{
	std::vector<AGUIElement* >::iterator		it;

	_buttons.clear();
	_listBox.clear();
	_input.clear();
	_cursorBox.clear();
	_checkBox.clear();

	it = _guiElement.begin();
	while (it != _guiElement.end())
	{
		delete ((*it));
		++it;
	}
	_guiElement.clear();
}

void	Menu::setButtonSprite()
{
	std::vector<Button>::iterator		it;

	it = _buttons.begin();
	while (it != _buttons.end())
	{
		it->setBackgroundSprite("../../res/img/button.png");
		it->setBackgroundOverSprite("../../res/img/buttonOver.png");
		++it;
	}
}

void Menu::initButton()
{
	Button		play(_graph, _event, Rect(380, 200, 90, 310), "PLAY");
	Button		quit(_graph, _event, Rect(380, 550, 90, 310), "QUIT");
	Button		option(_graph, _event, Rect(380, 380, 90, 310), "OPTION");
	RectDecor	*bottomDecor = new RectDecor(_graph, _event, Rect(290, 150, 50, 500));
	RectDecor	*topDecor = new RectDecor(_graph, _event, Rect(290, 650, 50, 500));
	RectDecor	*vaisseau = new RectDecor(_graph, _event, Rect(290, 650, 30, 70));

	_pagenb = PAGE::ACCEUIL;
	t1 = std::chrono::high_resolution_clock::now();
	clear();
	bottomDecor->setBackgroundSprite("../../res/img/bordureHaut.png");
	topDecor->setBackgroundSprite("../../res/img/bordureBas.png");
	vaisseau->setTransparentColor(Color(0, 0, 0));
	vaisseau->setBackgroundSprite("../../res/img/vaisseau1.png");
	play.setTextPos(70, 10);
	play.setTextSize(60);
	quit.setTextPos(70, 10);
	quit.setTextSize(60);
	option.setTextPos(20, 10);
	option.setTextSize(60);
	_buttons.push_back(play);
	_buttons.push_back(option);
	_buttons.push_back(quit);
	_guiElement.push_back(bottomDecor);
	_guiElement.push_back(topDecor);
	_guiElement.push_back(vaisseau);
	setButtonSprite();
}

void Menu::firstAnim(const int i, std::vector<Button>::iterator	it)
{
	Rect								tmp;
	std::chrono::high_resolution_clock::time_point        t2;

	if (_animInc < 190 * i && _first)
	{
		t2 = std::chrono::high_resolution_clock::now();
		_animDuration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
		if (_animDuration > ANIMDURATION)
		{
			t1 = std::chrono::high_resolution_clock::now();
			_animInc++;
		}
		tmp = it->getPos();
		it->setPos(Rect(tmp.getX(), _animInc, tmp.getHeight(), tmp.getWidth()));
	}
}

void Menu::drawButton()
{
	std::vector<Button>::iterator		it;
	int									i;

	it = _buttons.begin();
	i = 1;
	while (it != _buttons.end())
	{
		firstAnim(i, it);
		it->draw();
		++it;
		i++;
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

void	Menu::drawInput()
{
	std::vector<InputBox>::iterator		itInput;

	itInput = _input.begin();
	while (itInput != _input.end())
	{
		itInput->draw();
		++itInput;
	}
}

void Menu::drawCursorBox()
{
	std::vector<CursorBox>::iterator		itCursor;

	itCursor = _cursorBox.begin();
	while (itCursor != _cursorBox.end())
	{
		itCursor->draw();
		++itCursor;
	}
}

void Menu::drawCheckBox()
{
	std::vector<CheckBox>::iterator		itCheck;

	itCheck = _checkBox.begin();
	while (itCheck != _checkBox.end())
	{
		itCheck->draw();
		++itCheck;
	}
}

void Menu::drawGUIElement()
{
	std::vector<AGUIElement* >::iterator		it;

	it = _guiElement.begin();
	while (it != _guiElement.end())
	{
		(*it)->draw();
		++it;
	}
}

void Menu::roomList()
{
	Button						play(_graph, _event, Rect(750, 600, 90, 310), "JOIN");
	Button						quit(_graph, _event, Rect(20, 600, 90, 310), "BACK");
	std::vector<std::string>	elements;
	ListBox						list(_graph, _event, Rect(100, 250, 300, 900));


	list.setButtonSprite("../../res/img/buttonRoom.png");
	list.setButtonOverSprite("../../res/img/buttonRoomOver.png");
	elements.push_back("ELEMENT 1");
	elements.push_back("ELEMENT NEXT");
	elements.push_back("ELEMENT NEXT");
	elements.push_back("ELEMENT NEXT");
	elements.push_back("ELEMENT NEXT");
	elements.push_back("ELEMENT NEXT");
	elements.push_back("ELEMENT NEXT");
	elements.push_back("ELEMENT NEXT NEXT");
	elements.push_back("ELEMENT NEXT NEXT");
	elements.push_back("ELEMENT NEXT NEXT");
	elements.push_back("ELEMENT NEXT NEXT");
	elements.push_back("ELEMENT NEXT NEXT");
	elements.push_back("ELEMENT NEXT NEXT");
	elements.push_back("ELEMENT NEXT NEXT");
	elements.push_back("ELEMENT NEXT NEXT NEXT");
	list.setElements(elements);
	clear();
	_pagenb = PAGE::ROOMLIST;
	play.setTextPos(70, 10);
	play.setTextSize(60);
	quit.setTextPos(70, 10);
	quit.setTextSize(60);
	_buttons.push_back(play);
	_buttons.push_back(quit);
	_listBox.push_back(list);
	setButtonSprite();
}

void Menu::createRoom()
{
	Button		play(_graph, _event, Rect(750, 600, 90, 310), "CREATE");
	Button		quit(_graph, _event, Rect(20, 600, 90, 310), "BACK");
	InputBox	input(_graph, _event, Rect(200, 300, 30, 700));

	_pagenb = PAGE::ROOMCREATE;
	clear();
	input.setEvent(_event);
	input.setGraph(_graph);
	input.setBackgroundSprite("../../res/img/buttonRoom.png");
	input.setTextColor(Color(255, 255, 255));
	play.setTextPos(25, 10);
	play.setTextSize(60);
	quit.setTextPos(70, 10);
	quit.setTextSize(60);
	_buttons.push_back(play);
	_buttons.push_back(quit);
	_input.push_back(input);
	setButtonSprite();
}

void Menu::settings()
{
	Button		play(_graph, _event, Rect(750, 600, 90, 310), "SAVE");
	Button		quit(_graph, _event, Rect(20, 600, 90, 310), "BACK");
	CursorBox	music(_graph, _event, Rect(300, 300, 30, 500));
	CursorBox	sound(_graph, _event, Rect(300, 500, 30, 500));
	CheckBox	check(_graph, _event, Rect(300, 200, 40, 40));

	_pagenb = PAGE::SETTINGS;
	_first = false;
	clear();
	play.setTextPos(70, 10);
	play.setTextSize(60);
	quit.setTextPos(70, 10);
	quit.setTextSize(60);
	sound.setBackgroundSprite("../../res/img/scrollBar.png");
	sound.setBackgroundOverSprite("../../res/img/scrollButton.png");
	music.setBackgroundSprite("../../res/img/scrollBar.png");
	music.setBackgroundOverSprite("../../res/img/scrollButton.png");
	check.setBackgroundSprite("../../res/img/coche.png");
	check.setCheckedSprite("../../res/img/cocheRempli.png");
	_buttons.push_back(play);
	_buttons.push_back(quit);
	_cursorBox.push_back(music);
	_cursorBox.push_back(sound);
	_checkBox.push_back(check);
	setButtonSprite();
}

void Menu::clickEvent()
{
	std::map<PAGE, funcPtr>::iterator			it;

	it = _funcPtr.begin();
	while (it != _funcPtr.end())
	{
		if (it->first == _pagenb)
		{
			_soundManager.play(_clickSound);
			((*this).*it->second)();
			return;
		}
		++it;
	}
}

char Menu::buttonEvent() //A CORRIGER
{
	std::vector<Button>::iterator		it;
	std::vector<ListBox>::iterator		itList;
	std::vector<InputBox>::iterator		itInput;
	std::vector<CursorBox>::iterator	itCursor;
	std::vector<CheckBox>::iterator		itCheck;

	itCheck = _checkBox.begin();
	while (itCheck != _checkBox.end())
	{
		itCheck->click();
		++itCheck;
	}
	itCursor = _cursorBox.begin();
	while (itCursor != _cursorBox.end())
	{
		itCursor->click();
		++itCursor;
	}
	itInput = _input.begin();
	while (itInput != _input.end())
	{
		itInput->getInput();
		itInput->click();
		++itInput;
	}
	itList = _listBox.begin();
	while (itList != _listBox.end())
	{
		std::cout << itList->click() << std::endl;
		++itList;
	}
	it = _buttons.begin();
	while (it != _buttons.end())
	{
		it->over();
		++it;
	}
	if (_buttons[0].click())
	{
		_soundManager.play(_clickSound);
		if (_pagenb == PAGE::ACCEUIL)
			roomButton();
		else if (_pagenb == PAGE::PLAY)
		{
			_soundManager.stopAll();
			_game.setGraph(_graph);
			_game.setEvent(_event);
			_game.launch();
			return (2); //Doit lancer le jeu
		}
	}
	else if (_buttons[1].click())
		clickEvent();
	else if (_pagenb == PAGE::PLAY && _buttons[3].click())
	{
		_soundManager.play(_clickSound);
		createRoom();
	}
	else if (_pagenb == PAGE::PLAY && _buttons[2].click())
	{
		_soundManager.play(_clickSound);
		roomList();
	}
	else if ((_pagenb == PAGE::ACCEUIL && _buttons[2].click()) || _event->getCloseEvent() || _event->getKeyStroke() == "ECHAP")
	{
		_soundManager.play(_clickSound);
		_graph->close();
	}
	return (0);
}

void Menu::roomButton()
{
	Button		play(_graph, _event, Rect(750, 600, 90, 310), "PLAY");
	Button		quit(_graph, _event, Rect(20, 600, 90, 310), "BACK");
	Button		join(_graph, _event, Rect(300, 380, 90, 500), "JOIN ROOM");
	Button		create(_graph, _event, Rect(300, 150, 90, 500), "CREATE ROOM");

	_pagenb = PAGE::PLAY;
	_first = false;
	clear();
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
	setButtonSprite();
}

bool Menu::launch()
{
	char ret;
	initButton();
	//_graph->setFullScreen(true);
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
		_graph->setBackground("../../res/img/background_menu3.jpg", 0.6f, 0.7f);
		drawButton();
		drawListBox();
		drawInput();
		drawCursorBox();
		drawCheckBox();
		drawGUIElement();
		_graph->drawText("Hen Type", 300, 0, 90, Color(135, 206, 250, 255), "../../res/fonts/Aerospace.ttf");
		if (_pagenb == PAGE::ROOMLIST)
			_graph->drawText("Choice a room", 350, 150, 40, Color(224, 224, 224, 255), "../../res/fonts/Aerospace.ttf");
		_graph->refresh();
	}
	return (false);
}

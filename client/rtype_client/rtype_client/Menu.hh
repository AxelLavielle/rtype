#pragma once

#include <vector>
#include "AMenu.hh"
#include "Button.hh"
#include "ListBox.hh"
#include "InputBox.hh"
#include "CursorBox.hh"

class Menu :
	public AMenu
{
public:
	Menu();
	virtual ~Menu();
	virtual bool init();
	virtual bool launch();
private:
	enum PAGE
	{
		ACCEUIL,
		PLAY,
		ROOMLIST,
		ROOMCREATE,
		SETTINGS
	};

	std::vector<Button>		_buttons;
	PAGE					_pagenb;
	std::vector<ListBox>	_listBox;
	std::vector<InputBox>	_input;
	std::vector<CursorBox>	_cursorBox;

	void initButton();
	void drawButton();
	void drawListBox();
	void drawInput();
	void drawCursorBox();
	void roomList();
	void createRoom();
	void settings();
	char buttonEvent();
	void roomButton();
	void clear();
};


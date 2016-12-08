#pragma once

#include <vector>
#include "AMenu.hh"
#include "Button.hh"
#include "ListBox.hh"

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

	void initButton();
	void drawButton();
	void drawListBox();
	void roomList();
	void createRoom();
	void settings();
	char buttonEvent();
	void roomButton();
};


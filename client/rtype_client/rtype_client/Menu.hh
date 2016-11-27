#pragma once

#include <vector>
#include "AMenu.hh"
#include "Button.hh"

class Menu :
	public AMenu
{
public:
	Menu();
	virtual ~Menu();
	virtual bool init();
	virtual bool launch();
private:
	std::vector<Button>		_buttons;

	void initButton();
	void drawButton();
	void ButtonEvent();
};


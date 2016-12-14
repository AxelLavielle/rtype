#pragma once

#include <vector>
#include <map>
#include <chrono>
#include <ctime>
#include "AMenu.hh"
#include "Button.hh"
#include "ListBox.hh"
#include "InputBox.hh"
#include "CursorBox.hh"
#include "CheckBox.hh"
#include "Game.hh"
#include "RectDecor.hh"
#include "Sound.hh"
#include "SFMLSound.hh"
#include "PathFileManager.hh"
#include "HomePage.hh"

#define ANIMDURATION 1000

class Menu :
	public AMenu
{
public:
	Menu();
	virtual ~Menu();
	virtual bool init();
	virtual bool launch();
private:
	typedef void (Menu:: *funcPtr)(void);
	enum PAGE
	{
		ACCEUIL,
		PLAY,
		ROOMLIST,
		ROOMCREATE,
		SETTINGS
	};

	std::vector<Button>			_buttons;
	PAGE						_pagenb;
	std::vector<ListBox>		_listBox;
	std::vector<InputBox>		_input;
	std::vector<CursorBox>		_cursorBox;
	std::vector<CheckBox>		_checkBox;
	std::vector<AGUIElement* >	_guiElement;
	Game						_game;
	int							_animInc;
	bool						_first;
	double						_animDuration;
	std::chrono::high_resolution_clock::time_point        t1;
	Sound						_music;
	Sound						_clickSound;
	SFMLSound					_soundManager;
	std::map<PAGE, funcPtr>		_funcPtr;
	PathFileManager				_fileManager;

	void initButton();
	void firstAnim(const int i, std::vector<Button>::iterator it);
	void drawButton();
	void drawListBox();
	void drawInput();
	void drawCursorBox();
	void drawCheckBox();
	void drawGUIElement();
	void roomList();
	void createRoom();
	void settings();
	void clickEvent();
	char buttonEvent();
	void roomButton();
	void clear();
	void setButtonSprite();
};


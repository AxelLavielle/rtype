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
#include "SettingsPage.hh"
#include "LobbyPage.hh"
#include "RoomListPage.hh"
#include "InsideRoomPage.hh"

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
	std::vector<AGUIElement* >	_guiElement;
	Game						_game;
	Sound						_music;
	Sound						_clickSound;
	SFMLSound					_soundManager;
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


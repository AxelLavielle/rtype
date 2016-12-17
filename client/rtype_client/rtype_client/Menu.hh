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
#include "InsideRoomPage.hh"
#include "EndGamePage.hh"
#include "CreateRoomPage.hh"

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
	APage						*_page;

	void initLobby();
};


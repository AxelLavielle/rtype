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
#include "PausePage.hh"
#include "ThreadPool.hh"
#include "CmdManager.hh"

#define RECO_DURATION 5000

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
	CmdManager					_cmdManager;

	std::chrono::high_resolution_clock::time_point        _t1Conn;

	void initLobby();
	bool tryToConnect();
};


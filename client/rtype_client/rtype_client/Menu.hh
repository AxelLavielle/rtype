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
#include "SettingsNextPage.hh"
#include "LobbyPage.hh"
#include "InsideRoomPage.hh"
#include "EndGamePage.hh"
#include "LoadingPage.hh"
#include "CreateRoomPage.hh"
#include "PausePage.hh"
#include "ThreadPool.hh"
#include "Thread.hh"
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
	virtual void setIp(const std::string &ip);
	virtual void setPort(const int port);
private:
	std::vector<AGUIElement* >	_guiElement;
	Game						_game;
	Sound						_music;
	Sound						_clickSound;
	SFMLSound					_soundManager;
	PathFileManager				_fileManager;
	APage						*_page;
	CmdManager					_cmdManager;
	std::string					_playerName;
	bool						_newEvent;
	std::string					_ip;
	int							_port;
	RoomInfoCmd					*_roomInfo;
	Mutex						_mutexReceive;
	Mutex						_mutexRun;
	bool						_run;
	bool						_checkGameReady;
	int							_id;
	Thread						*_th;
	SaveConfig					_sv;

	std::chrono::high_resolution_clock::time_point        _t1Conn;

	void initLobby();
	bool tryToConnect();
	void manageReco(Thread * th);
	void setRoomInfo(RoomInfoCmd * roomInfo, InsideRoomPage * page);
	void receiveData();
	void checkGameReady();
	void manageLaunchGame();
};


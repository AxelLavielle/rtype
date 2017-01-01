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
#define MENU_LOOP_DURATION (1)
#define MENU_RECEIVE_DURATION (10)
#define MENU_REFRESH_ROOM_LIST (1000)

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
	std::string					_playerName;
	bool						_newEvent;
	std::string					_ip;
	int							_port;
	RoomInfoCmd					*_roomInfo;
	Mutex						_mutexReceive;
	int							_id;
	Thread						*_th;
	SaveConfig					_sv;
	bool						_run;
	IPage::PAGE					_successEvent;
	IPage::PAGE					_errorEvent;
	std::chrono::high_resolution_clock::time_point			_t1Loop;
	IPage::PAGE												_curr_event;
	ListRoomCmd					*_roomList;
	Mutex						_mutexRun;
	Mutex						_mutexRoomList;
	bool						_getRoomList;

	std::chrono::high_resolution_clock::time_point        _t1Conn;

	void managePageEvent();
	void manageWaiting();
	void setRoomList();
	void setRoomInfo();
	bool refreshRoomInfo();
	void startGame();
	void reconnection();
	void receiveInfo();
};


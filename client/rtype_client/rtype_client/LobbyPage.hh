#pragma once

#include <chrono>
#include "APage.hh"
#include "ListRoomCmd.hh"

class LobbyPage :
	public APage
{
public:
	LobbyPage(IGraphManager *graph, IEventManager *event, const PathFileManager &fileManager, ISoundManager *soundManager);
	virtual ~LobbyPage();
	virtual bool			init();
	virtual void			clear();
	virtual bool			launch();
	virtual void			draw();
	virtual IPage::PAGE		event();
	void					addRoom(RoomIdInfos);
	RoomIdInfos				getSelectedRoom() const;

private:
	Sound											_clickSound;
	std::vector<RoomIdInfos>						_room;
	std::vector<std::string>						_roomName;
};


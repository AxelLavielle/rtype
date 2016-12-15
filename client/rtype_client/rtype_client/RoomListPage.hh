#pragma once

#include <chrono>
#include "APage.hh"

class RoomListPage :
	public APage
{
public:
	RoomListPage(IGraphManager *graph, IEventManager *event, const PathFileManager &fileManager, ISoundManager *soundManager);
	virtual ~RoomListPage();
	virtual bool			init();
	virtual void			clear();
	virtual bool			launch();
	virtual void			draw();
	virtual IPage::PAGE		event();

private:
	std::chrono::high_resolution_clock::time_point        t1;
	Sound						_clickSound;

	void firstAnim();

};


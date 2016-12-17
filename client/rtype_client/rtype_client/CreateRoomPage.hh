#pragma once

#include "APage.hh"

class CreateRoomPage :
	public APage
{
public:
	CreateRoomPage(IGraphManager *graph, IEventManager *event, const PathFileManager &fileManager, ISoundManager *soundManager);
	virtual ~CreateRoomPage();
	virtual bool			init();
	virtual void			clear();
	virtual bool			launch();
	virtual void			draw();
	virtual IPage::PAGE	event();
private:
	Sound						_clickSound;
};


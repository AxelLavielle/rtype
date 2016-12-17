#pragma once

#include "APage.hh"

class						EndPage : public APage
{
public:
	EndPage(IGraphManager *, IEventManager *, const PathFileManager &, ISoundManager *);
	virtual ~EndPage();

	virtual bool			init();
	virtual void			clear();
	virtual bool			launch();
	virtual void			draw();
	virtual IPage::PAGE		event();

private:
	Sound					_clickSound;
};

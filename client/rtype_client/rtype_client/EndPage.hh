#pragma once

#include "APage.hh"

class EndPage : public APage
{
public:
	EndPage();
	virtual ~EndPage();

	virtual bool			init();
	virtual void			clear();
	virtual bool			launch();
	virtual void			draw();
	virtual IPage::PAGE		event();
};

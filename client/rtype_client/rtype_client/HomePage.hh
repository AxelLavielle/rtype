#pragma once

#include "APage.hh"

class HomePage :
	public APage
{
public:
	HomePage();
	virtual ~HomePage();
	virtual bool			init();
	virtual void			clear();
	virtual bool			launch();
	virtual void			draw();
};


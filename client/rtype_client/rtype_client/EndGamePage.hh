#pragma once

#include "APage.hh"

class								EndGamePage : public APage
{
public:
	EndGamePage(IGraphManager *, IEventManager *, const PathFileManager &, ISoundManager *);
	virtual ~EndGamePage();

	virtual bool					init();
	virtual void					clear();
	virtual bool					launch();
	virtual void					draw();
	virtual IPage::PAGE				event();

private:
	Sound							_clickSound;
	std::vector < std::pair<std::string, int>> _scores;
};

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
	void							addPlayer(const std::string &, const int);
	void							setWave(const int);
	void							setVictory(const bool);

private:
	Sound							_clickSound;
	std::vector < std::pair<std::string, int>> _scores;
	int								_destroyedWaves;
	std::string						_msg;
};

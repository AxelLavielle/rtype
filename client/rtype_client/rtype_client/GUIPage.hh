#pragma once
#include "APage.hh"
class GUIPage :	public APage
{
public:
	GUIPage(IGraphManager *graph, IEventManager *event, const PathFileManager &fileManager, ISoundManager *soundManager);
	virtual ~GUIPage();
	virtual bool			init();
	virtual void			clear();
	virtual bool			launch();
	virtual void			draw();
	virtual IPage::PAGE		event();

private:
	int						_hp;
	int						_def;
	int						_nbPlayers;
	int						_score;
	std::string				_mode;
	std::string				_playerName;
};


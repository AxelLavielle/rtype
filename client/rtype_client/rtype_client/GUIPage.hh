#pragma once

#define ANIMDURATION_G 500
#define ANIMDURATION_B 500

#include "APage.hh"
#include <chrono>

class GUIPage :	public APage
{
public:
	GUIPage(IGraphManager *graph, IEventManager *event, const PathFileManager &fileManager, ISoundManager *soundManager);
	virtual ~GUIPage();
	virtual bool											init();
	virtual void											clear();
	virtual bool											launch();
	virtual void											draw();
	virtual IPage::PAGE										event();
	void													setHp(const int hp);
	void													setDef(const int df);
	void													setNbPlayer(const int nbPlayer);
	void													setScore(const int score);
	void													setMode(const std::string & mode);
	void													setPlayerName(const std::string & name);
	int														getTopBarHeight() const;
	int														getBottomBarHeight() const;

private:
	void													titleAnimation();

	int														_hp;
	int														_def;
	int														_nbPlayers;
	int														_score;
	std::string												_mode;
	std::string												_playerName;
	int														_animInc;
	double													_animDuration;
	std::chrono::high_resolution_clock::time_point			_t1;
	int														_textPosX;
	int														_textPosY;
	int														_topBarHeight;
	int														_bottompBarHeight;
};


#pragma once

#define ANIMDURATION_L 5000

#include "APage.hh"
#include <chrono>

class LoadingPage : public APage
{
public:
	LoadingPage(IGraphManager *graph, IEventManager *event, const PathFileManager &fileManager, ISoundManager *soundManager);
	virtual ~LoadingPage();
	virtual bool											init();
	virtual void											clear();
	virtual bool											launch();
	virtual void											draw();
	virtual IPage::PAGE										event();
	void													setText(const std::string &);
	void													setTextPos(const int);

private:
	void													loadingAnim();

	int														_animInc;
	int														_animInc2;
	double													_animDuration;
	std::string												_text;
	int														_textPos;
	std::chrono::high_resolution_clock::time_point			t1;
};

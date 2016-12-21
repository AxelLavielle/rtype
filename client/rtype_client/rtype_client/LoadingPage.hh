#pragma once

#define ANIMDURATION 500

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

private:
	void													loadingAnim();

	int														_animInc;
	double													_animDuration;
	std::chrono::high_resolution_clock::time_point			t1;
};

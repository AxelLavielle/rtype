#pragma once

#define ANIMDURATION 20000

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
	int														_animInc2;
	int														_animInc3;
	int														_animInc4;
	int														_imgW;
	int														_img2W;
	int														_img3W;
	int														_img4W;
	double													_animDuration;
	std::chrono::high_resolution_clock::time_point			t1;
};

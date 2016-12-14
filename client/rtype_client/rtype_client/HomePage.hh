#pragma once

#include <chrono>
#include "APage.hh"

#define ANIMDURATION 1000

class HomePage :
	public APage
{
public:
	HomePage(IGraphManager *graph, IEventManager *event, const PathFileManager &fileManager, ISoundManager *soundManager);
	virtual ~HomePage();
	virtual bool			init();
	virtual void			clear();
	virtual bool			launch();
	virtual void			draw();
	virtual IPage			*event();

private:
	int							_animInc;
	std::chrono::high_resolution_clock::time_point        t1;
	double						_animDuration;

	void firstAnim();

};


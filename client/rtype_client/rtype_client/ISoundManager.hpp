#pragma once

#include "Sound.hh"

class ISoundManager
{
public:
	virtual ~ISoundManager() {}
	virtual bool init() = 0;
	virtual bool play(const Sound & sound) = 0;
	virtual bool stop(const Sound & sound) = 0;
	virtual bool pause(const Sound & sound) = 0;
};


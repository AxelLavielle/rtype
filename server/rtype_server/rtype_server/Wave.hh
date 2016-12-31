#pragma once

#include "IEntity.hpp"
#include "RedSpiralMonster.hh"
#include "FireTacleMonster.hh"
#include "BolidFighterMonster.hh"
#include "BossMonster.hh"
#include <queue>

#define MAX_ENTITIES		(50)
#define INITIAL_TIME		(50)
#define TIME_BETWEEN_WAVE	(100)
#define NB_CELLS_Y			(80)
#define NB_CELLS_X			(160)

typedef	std::pair<int, IEntity *>	WaveElement;

class Wave
{
private:
	int						_time;
	std::queue<WaveElement>	_waveEntities;
	int						_nbEntities;

	void					redWave(const int);
	IEntity					*getRandomMonster(const int, const int);
	IEntity					*getNewMonster(const int, const int, const int);

public:
	Wave();
	Wave(const int);
	~Wave();

	void					generate();
	void					generateBoss();
	std::vector<IEntity *>	getEntities(const int);
	bool					isOver() const;
};


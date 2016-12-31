#pragma once

#include "IEntity.hpp"
#include "Monster.hh"
#include <queue>

#define MAX_ENTITIES	(50)
#define INITIAL_TIME	(50)
#define NB_CELLS_Y		(80)
#define NB_CELLS_X		(160)

typedef	std::pair<int, IEntity *>	WaveElement;

class Wave
{
private:
	std::queue<WaveElement>	_waveEntities;
	int						_nbEntities;
	void					redWave(int &, const int);

public:
	Wave();
	Wave(const int);
	~Wave();

	void					generate();
	std::vector<IEntity *>	getEntities(const int);
	bool					isOver() const;
};


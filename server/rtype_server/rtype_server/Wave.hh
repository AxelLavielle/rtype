#pragma once

#include "DlManager.hh"
#include "IEntity.hpp"
#include <queue>

#define MAX_ENTITIES		(50)
#define INITIAL_TIME		(50)
#define TIME_BETWEEN_WAVE	(30)
#define NB_CELLS_Y			(80)
#define NB_CELLS_X			(160)

typedef	std::pair<int, IEntity *>			WaveElement;
typedef	std::pair<IEntity *, std::string>	DynamicLib;

class Wave
{
private:
	int						_time;
	std::queue<WaveElement>	_waveEntities;
	int						_nbEntities;
  DlManager						*_dlManager;
  std::vector<DynamicLib>				_bossEntities;
  std::vector<DynamicLib>				_monsterEntities;

  void	refreshEntities(const std::vector<DynamicLib> &);
	void					getMiniWave(const int);
	IEntity					*getNewMonster(const int, const int, const int);

public:
	Wave(DlManager *);
  Wave(const int, DlManager *);
	~Wave();

  void					generate();
	IEntity					*generateBoss();
	std::vector<IEntity *>	getEntities(const int);
	bool					isOver() const;
};

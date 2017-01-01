
#include "Wave.hh"

Wave::Wave(DlManager *dlM)
{
	_nbEntities = std::rand() % MAX_ENTITIES;
	_time = INITIAL_TIME;
	_dlManager = dlM;
}

Wave::Wave(const int nbEntities, DlManager *dlM)
{
	if (nbEntities > MAX_ENTITIES || nbEntities <= 0)
		_nbEntities = MAX_ENTITIES;
	else
		_nbEntities = nbEntities;
	_time = INITIAL_TIME;
	_dlManager = dlM;
}

Wave::~Wave()
{
}

IEntity	*Wave::getNewMonster(const int x, const int y, const int type)
{
  IEntity *newEntity;

  if (static_cast<size_t>(type) >= _monsterEntities.size())
    {
      std::cout << "NO MONSTER" << std::endl;
      return (NULL);
    }
  else
    newEntity = _dlManager->getInstance(_monsterEntities.at(type).second);

  if (newEntity)
  {
	  newEntity->setPosX(x);
	  newEntity->setPosY(y);
	  newEntity->refresh();
  }
  else
	  std::cout << "NEW ENTITY IS NULL" << std::endl;
  return (newEntity);
}

void	Wave::getMiniWave(const int nbMonsters)
{
	int		x;
	int		y;
	int		i;

	i = 0;
	x = NB_CELLS_X;
	y = std::rand() % (NB_CELLS_Y / 3) + 15;

	if (_monsterEntities.size() == 0)
	  {
	    std::cout << "NO MONSTERS" << std::endl;
	    return;
	  }
	int type = std::rand() % _monsterEntities.size();

	while (i < nbMonsters)
	{
		IEntity *newMonster = getNewMonster(x, y, type);
		if (newMonster)
		  {
		    _waveEntities.push(std::make_pair(_time, newMonster));
//			std::cout << "===================================> Adding new Entity to the Wave time [" << _time << "]" << std::endl;
		    _time += newMonster->getHeight();
		  }
		i++;
	}

}

void						Wave::refreshEntities(const std::vector<DynamicLib> &entities)
{
  std::vector<DynamicLib>::const_iterator	it;
  size_t					found;

  it = entities.begin();
  while (it != entities.end())
    {
      found = (*it).second.find("Boss");
      if (found == std::string::npos)
		_monsterEntities.push_back(*it);
      else
		_bossEntities.push_back(*it);
      it++;
    }
}

void	Wave::generate()
{
	int		i;
	int		nb;

	std::cout << "GENERATING WAVE" << std::endl;
	_dlManager->refresh();
	refreshEntities(_dlManager->getAlldl());
	i = 0;
	while (i < _nbEntities)
	{
		nb = _nbEntities;
		getMiniWave(nb);
		_time += TIME_BETWEEN_WAVE;
		i += nb;
	}
}

IEntity	*Wave::generateBoss()
{
	int x = NB_CELLS_X;
	int y = (NB_CELLS_Y / 3);
	IEntity *newBoss = NULL;

	_time += TIME_BETWEEN_WAVE;

	if (_bossEntities.size() > 0)
	  {
	    newBoss = _dlManager->getInstance(_bossEntities.at(0).second);
	    newBoss->setPosX(x - 20);
	    newBoss->setPosY(y);
	    newBoss->refresh();
	    _waveEntities.push(std::make_pair(_time, newBoss));
	  }
	return (newBoss);
}

std::vector<IEntity*>		Wave::getEntities(const int time)
{
	std::vector<IEntity*>	entities;
	WaveElement				current;

	while (_waveEntities.size() > 0 && (current = _waveEntities.front()).first < time)
	{
		entities.push_back(current.second);
		_waveEntities.pop();
	}
	return (entities);
}

bool		Wave::isOver() const
{
	return (_waveEntities.size() == 0);
}

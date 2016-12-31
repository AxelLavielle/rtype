#include "Wave.hh"

Wave::Wave()
{
	_nbEntities = std::rand() % MAX_ENTITIES;
	_time = INITIAL_TIME;
}

Wave::Wave(const int nbEntities)
{
	if (nbEntities > MAX_ENTITIES || nbEntities <= 0)
		_nbEntities = MAX_ENTITIES;
	else
		_nbEntities = nbEntities;
	_time = INITIAL_TIME;
}

Wave::~Wave()
{
}

IEntity	*Wave::getRandomMonster(const int x, const int y)
{
	switch (std::rand() % 3)
	{
	case 0:
		return (new FireTacleMonster(x, y));
	case 1:
		return (new BolidFighterMonster(x, y));
	case 2:
		return (new RedSpiralMonster(x, y));
	default:
		return (new FireTacleMonster(x, y));
	}
}

IEntity	*Wave::getNewMonster(const int x, const int y, const int type)
{
	switch (type)
	{
	case 0:
		return (new FireTacleMonster(x, y));
	case 1:
		return (new BolidFighterMonster(x, y));
	case 2:
		return (new RedSpiralMonster(x, y));
	default:
		return (new FireTacleMonster(x, y));
	}
}

void	Wave::redWave(const int nbMonsters)
{
	int		x;
	int		y;
	int		i;

	i = 0;
	x = NB_CELLS_X;
	y = (NB_CELLS_Y / 2);

	//IEntity *newMonster = getRandomMonster(x, y);
	int type = std::rand() % 3;
	while (i < nbMonsters)
	{
		IEntity *newMonster = getNewMonster(x, y, type);
		_waveEntities.push(std::make_pair(_time, newMonster));
		std::cout << "===================================> Adding new Entity to the Wave time [" << _time << "]" << std::endl;
		_time += newMonster->getHeight();
		i++;
	}

}

void	Wave::generate()
{
	int	i;
	int nb;

	i = 0;
	while (i < _nbEntities)
	{
		nb = std::rand() % (_nbEntities / 3) + 3;
		redWave(nb);
		_time += TIME_BETWEEN_WAVE;
		i += nb;
	}
}

void Wave::generateBoss()
{
	int	x = NB_CELLS_X;
	int y = (NB_CELLS_Y / 2);
	std::cout << "BOSS IS COMING !" << std::endl;
	_time += TIME_BETWEEN_WAVE;

	IEntity *newBoss = new BossMonster(x, y);
	_waveEntities.push(std::make_pair(_time, newBoss));
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

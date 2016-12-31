#include "Wave.hh"

Wave::Wave()
{
	_nbEntities = std::rand() % MAX_ENTITIES;
}

Wave::Wave(const int nbEntities)
{
	if (nbEntities > MAX_ENTITIES)
		_nbEntities = MAX_ENTITIES;
	else
		_nbEntities = nbEntities;
}

Wave::~Wave()
{
}

void	Wave::redWave(int &time, const int nbMonsters)
{
	int		x;
	int		y;
	int		i;

	i = 0;
	x = NB_CELLS_X;
	y = (NB_CELLS_Y / 2);

	while (i < nbMonsters)
	{
		IEntity *newMonster = new Monster(x, y);
		_waveEntities.push(std::make_pair(time, newMonster));
		std::cout << std::endl << "===================================> Adding new Entity to the Wave time [" << time << "]" << std::endl;
		time += newMonster->getHeight();
		i++;
	}

}

void	Wave::generate()
{
	int	i;
	int	time;

	i = 0;
	time = INITIAL_TIME;
	while (i < _nbEntities)
	{
		redWave(time, 5);
		time += 200;
		i += 5;
	}
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

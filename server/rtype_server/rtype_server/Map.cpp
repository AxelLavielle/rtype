#include "Map.hh"

Map::Map()
{
}

Map::Map(const int nbCellsX) : _entityList(nbCellsX * NB_CELLS_Y, NULL)
{
	_nbCellsX = nbCellsX;
}

Map::~Map()
{
}

void		Map::generate()
{
	int		i;
	int		nbEntities;
	int		x;
	int		y;

	IEntity *walle = new Barrier(50, 50);
	setEntity(walle);

	return;
	/*x = 0;
	y = 0;
	while (x < _nbCellsX)
	{
		if ((*this)(x, y) == NULL)
		{
			IEntity *wall = new Barrier(x, y);
			setEntity(wall);
		}
		x++;
	}
	x = 0;
	y = NB_CELLS_Y - 1;
	while (x < _nbCellsX)
	{
		if ((*this)(x, y) == NULL)
		{
			IEntity *wall = new Barrier(x, y);
			setEntity(wall);
		}
		x++;
	}
*/
	IEntity *wall = new Barrier(0, 0);
	setEntity(wall);
	i = 0;
	nbEntities = 3;
	while (i < nbEntities)
	{
		x = std::rand() % _nbCellsX + 20;
		y = std::rand() % NB_CELLS_Y;
		if ((*this)(x, y) == NULL)
		{
			IEntity *wall = new Barrier(x, y);
			setEntity(wall);
			i++;
		}
	}
}

int	Map::getNbEntities() const
{
	int										nb;
	std::vector<IEntity *>::const_iterator	it;

	nb = 0;
	it = _entityList.begin();
	while (it != _entityList.end())
	{
		if ((*it))
			nb++;
		it++;
	}
	return (nb);
}

std::vector<IEntity *>		Map::getEntityList() const
{
	return (_entityList);
}

void						Map::setEntityList(const std::vector<IEntity *> &entityList)
{
	_entityList = entityList;
}

IEntity						*Map::operator()(const int x, const int y)
{
	if ((x > 0 && x < _nbCellsX) && (y > 0 && y < NB_CELLS_Y))
		return (_entityList.at(x + y * NB_CELLS_Y));
	return (NULL);
}

std::vector<IEntity*>						Map::getEntities(const int xMin, const int xMax) const
{
	std::vector<IEntity *>					goodEntities;
	std::vector<IEntity *>::const_iterator	it;

	it = _entityList.begin();
	while (it != _entityList.end())
	{
		if ((*it) && (*it)->getPosX() >= xMin && (*it)->getPosX() < xMax)
			goodEntities.push_back(*it);
		it++;
	}
	return (goodEntities);
}

void Map::setEntity(IEntity *newEntity)
{
	int x;
	int y;

	x = newEntity->getPosX();
	y = newEntity->getPosY();
	if ((x > 0 && x < _nbCellsX) && (y > 0 && y < NB_CELLS_Y))
	{
		std::cout << "SET ENTITY MAP (" << x << ", " << y << ") TYPE : " << newEntity->getType() << std::endl;
		_entityList.at(x + y * NB_CELLS_Y) = newEntity;
	}

}

void									Map::refresh()
{
	std::vector<IEntity *>				entities;
	std::vector<IEntity *>::iterator	it;

	//std::cout << "[Game] : Refreshing Map" << std::endl;
	entities = getEntities(0, _nbCellsX);
	_entityList.assign(_nbCellsX * NB_CELLS_Y, NULL);

	it = entities.begin();
	while (it != entities.end())
	{
		setEntity(*it);
		it++;
	}
}
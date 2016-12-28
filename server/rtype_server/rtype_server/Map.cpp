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
		//std::cout << "SET ENTITY MAP (" << x << ", " << y << ") = " << x + y * NB_CELLS_Y << std::endl;
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
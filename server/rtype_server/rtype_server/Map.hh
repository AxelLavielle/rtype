#pragma once

# include <vector>
# include "AEntity.hh"
#include "Serialize.hh"

#include <iostream>

#define NB_CELLS_Y (80)

class							Map
{
public:
	Map();
	Map(const int);
	~Map();

	std::vector<IEntity *>		getEntityList() const;
	void						setEntityList(const std::vector<IEntity *> &);
	IEntity						*operator()(const int, const int);
	std::vector<IEntity *>		getEntities(const int, const int) const;
	void						setEntity(IEntity *);
	void						refresh();
	void						generate();
	int							getNbEntities() const;

private:
	std::vector<IEntity *>		_entityList;
	int							_nbCellsX;
};


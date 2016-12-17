#pragma once

# include <vector>
# include "AEntity.hh"

class							Map
{
public:
	Map();
	~Map();

	std::vector<IEntity *>		getEntityList() const;
	void						setEntityList(const std::vector<IEntity *> &);

private:
	std::vector<IEntity *>		_entityList;
};


#pragma once

#include "IEntity.hpp"

class IEntity;

class CollisionBox
{
private:
	IEntity	*_object;

public:
	CollisionBox(IEntity *);
	~CollisionBox();

	int		getX() const;
	int		getY() const;
	int		getWidth() const;
	int		getHeight() const;
	bool	isColliding(CollisionBox *) const;
};

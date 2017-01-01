#include "stdafx.h"
#include "CollisionBox.hh"

CollisionBox::CollisionBox(IEntity *object)
{
	_object = object;
}


CollisionBox::~CollisionBox()
{
}

int CollisionBox::getX() const
{
	return (_object->getPosX());
}

int CollisionBox::getY() const
{
	return (_object->getPosY());
}

int CollisionBox::getWidth() const
{
	return (_object->getWidth());
}

int CollisionBox::getHeight() const
{
	return (_object->getHeight());
}


bool	CollisionBox::isColliding(CollisionBox *other) const
{
	if (getX() < other->getX() + other->getWidth()
		&& getX() + getWidth() > other->getX()
		&& getY() < other->getY() + other->getHeight()
		&& getY() + getHeight() > other->getY())
	{
		//std::cout << "COLLIDING !!!" << std::endl;
		return (true);
	}
	return (false);
}


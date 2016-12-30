#pragma once

#include "EntityType.hh"
#include "CollisionBox.hh"

#include <vector>
#include <string>
#include <iostream>

class CollisionBox;

class IEntity
{
public:
	virtual					~IEntity()
	{}

	virtual void			update() = 0;
	virtual double			getPosX() const = 0;
	virtual void			setPosX(const double) = 0;
	virtual double			getPosY() const = 0;
	virtual void			setPosY(const double) = 0;
	virtual double			getHeight() const = 0;
	virtual void			setHeight(const double) = 0;
	virtual double			getWidth() const = 0;
	virtual void			setWidth(const double) = 0;
	virtual double			getSpeedX() const = 0;
	virtual void			setSpeedX(const double) = 0;
	virtual double			getSpeedY() const = 0;
	virtual void			setSpeedY(const double) = 0;
	virtual rtype::EntityType	getType() const = 0;
	virtual void			setType(const rtype::EntityType&) = 0;
	virtual std::string		getName() const = 0;
	virtual void			setName(const std::string &) = 0;
	virtual int				getLife() const = 0;
	virtual void			setLife(const int) = 0;
	virtual std::string		getSpriteRepo() const = 0;
	virtual void			setSpriteRepo(const std::string &) = 0;
	virtual void			setId(const unsigned int) = 0;
	virtual unsigned int	getId() const = 0;
	virtual bool			isDead() const = 0;
	virtual void			setDead(const bool) = 0;
	virtual		bool			setArgs(const std::string & args) = 0;
	virtual		std::string		getArgs() const = 0;
	virtual CollisionBox		*getCollisionBox() const = 0;
	virtual bool			isColliding(CollisionBox *) const = 0;
	virtual void			refresh() = 0;
};

#pragma once

#include <string>
#include "EntityType.hh"

class IEntity
{
public:
	virtual				~IEntity(){}
	virtual void			update() = 0;
	virtual double			getPosX(void) const = 0;
	virtual void			setPosX(const double) = 0;
	virtual double			getPosY(void) const = 0;
	virtual void			setPosY(const double) = 0;
	virtual double			getSpeedX(void) const = 0;
	virtual void			setSpeedX(const double) = 0;
	virtual double			getSpeedY(void) const = 0;
	virtual void			setSpeedY(const double) = 0;
	virtual void			setType(const rtype::EntityType&) = 0;
	virtual rtype::EntityType	getType() const = 0;
	virtual void			setName(const std::string &) = 0;
	virtual std::string		getName() const = 0;
	virtual void			setLife(const int) = 0;
	virtual int			getLife() const = 0;
	virtual std::string		getSpriteRepo() const = 0;
	virtual void			setSpriteRepo(const std::string &) = 0;
};

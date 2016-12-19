#pragma once

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
	virtual void			setType(const rtype::EntityType&) = 0;
	virtual rtype::EntityType	getType() const = 0;
	virtual void			setName(const std::string &) = 0;
	virtual std::string		getName() const = 0;
	virtual IEntity			*createEntity() = 0;
	virtual std::sting		getSpriteRepo() = 0;
	virtual void			setSpriteRepo(const std::string &) = 0;
};

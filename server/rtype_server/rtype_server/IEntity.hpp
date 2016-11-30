#pragma once

class IEntity
{
public:
	virtual		~IEntity(){}
	virtual double	getPosX(void) const = 0;
	virtual void	setPosX(const double) = 0;
	virtual double	getPosY(void) const = 0;
	virtual void	setPosY(const double) = 0;
};

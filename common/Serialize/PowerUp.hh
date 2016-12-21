#pragma once

#include "AEntity.hh"

class PowerUp :
  public AEntity
{
private:
  int		_power;
public:
  PowerUp();
  virtual ~PowerUp();

  virtual void	update();

  IEntity	*createEntity();
  void		setPower(const int);
  int		getPower() const;
};

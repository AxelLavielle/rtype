#pragma once

#include "AEntity.hh"

class PowerUp :
  public AEntity
{
protected:
  int		_power;
public:
  PowerUp();
  virtual	~PowerUp();

  virtual void	update();
  void	setPower(const int);
  int	getPower(void) const;
};

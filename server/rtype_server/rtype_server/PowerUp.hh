#pragma once

#include "AEntity.hh"

class PowerUp :
  public AEntity
{
public:
  PowerUp();
  virtual	~PowerUp();
  virtual void	setPower(const int);
  virtual int	getPower(void) const;
  virtual void	update(void);
protected:
  int		_power;
};

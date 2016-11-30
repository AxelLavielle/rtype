#include "PowerUp.hh"

PowerUp::PowerUp()
{
}

PowerUp::~PowerUp()
{
}

int		PowerUp::getPower() const
{
  return (_power);
}

void		PowerUp::setPower(const int power)
{
  _power = power;
}

void		PowerUp::update(void)
{
}

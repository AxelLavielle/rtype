#include "PowerUp.hh"

PowerUp::PowerUp()
{
  this->setType(rtype::POWER_UP);
  refresh();
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

void		PowerUp::update()
{
}

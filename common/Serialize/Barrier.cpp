#include "Barrier.hh"

Barrier::Barrier()
{
  this->setType(rtype::BARRIER);
}

Barrier::~Barrier()
{
}

void	Barrier::update(void)
{
}

extern "C" IEntity	*Barrier::createEntity()
{
  return (new Barrier);
}

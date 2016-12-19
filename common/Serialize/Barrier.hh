#pragma once

#include "AEntity.hh"

class Barrier :
  public AEntity
{
public:
  Barrier();
  IEntity		*createEntity();
  virtual		~Barrier();
  virtual void		update();
};

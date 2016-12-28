#pragma once

#include "AEntity.hh"

class Barrier : public AEntity
{
public:
  Barrier(const int, const int);
  virtual ~Barrier();

  virtual void		update();

  IEntity		*createEntity();
};

#pragma once

#include "AEntity.hh"

class Barrier :
  public AEntity
{
public:
  Barrier();
  virtual		~Barrier();

  virtual void		update();
};

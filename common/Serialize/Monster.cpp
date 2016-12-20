#include "Monster.hh"

Monster::Monster()
{
  this->setType(rtype::MONSTER);
  this->setName("Monster1");
}

Monster::~Monster()
{
}

void		Monster::setId(const int id)
{
  _id = id;
}

int		Monster::getId() const
{
  return (_id);
}

void		Monster::update()
{
}

extern "C" IEntity	*createEntity()
{
  return (new Monster);
}

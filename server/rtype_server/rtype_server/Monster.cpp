#include "Monster.hh"

Monster::Monster()
{
  this->setType(rtype::MONSTER);
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

void		Monster::setName(const std::string &name)
{
  _name = name;
}

std::string	Monster::getName(void) const
{
  return (_name);
}

void		Monster::update(void)
{
}

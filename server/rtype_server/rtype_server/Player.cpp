#include "Player.hh"
#include "EntityType.hh"

Player::Player()
{
  this->setType(rtype::PLAYER);
}

Player::~Player()
{
}

int		Player::getId(void) const
{
  return (_id);
}

void		Player::setId(const int id)
{
  _id = id;
}

std::string	Player::getName(void) const
{
  return (_name);
}

void		Player::setName(const std::string &name)
{
  _name = name;
}

void		Player::update(void)
{
}

extern "C" IEntity	*createEntity()
{
  return (new Player);
}

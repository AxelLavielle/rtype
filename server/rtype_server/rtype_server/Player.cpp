#include "Player.hh"
#include "EntityType.hh"

Player::Player()
{
  this->setType(rtype::PLAYER);
  this->setName("Player1");
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

void		Player::update(void)
{
}

extern "C" IEntity	*createEntity()
{
  return (new Player);
}

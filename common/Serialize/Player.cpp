#include "Player.hh"
#include "EntityType.hh"

Player::Player()
{
  this->setType(rtype::PLAYER);
  this->setName("Player1");
}

Player::Player(const std::string &name)
{
	this->setType(rtype::PLAYER);
	this->setName(name);
}

Player::~Player()
{
}

int		Player::getId() const
{
  return (_id);
}

void		Player::setId(const int id)
{
  _id = id;
}

void		Player::update()
{
}

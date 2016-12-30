#include "Player.hh"
#include "EntityType.hh"

Player::Player(const int x, const int y)
{
  this->setType(rtype::PLAYER);
  this->setName("");
  this->setPosX(x);
  this->setPosY(y);
  this->setHeight(3);
  this->setWidth(5);
  this->setSpeedX(1);
  this->setSpeedY(1);
  this->setLife(100);
  this->setSpriteRepo("/res/img/spaceShip10.png");
  _missileCooldown = 0;
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

int			Player::getMissileCooldown() const
{
	return (_missileCooldown);
}

void		Player::setMissileCooldown(const int mC)
{
	_missileCooldown = mC;
}

void		Player::update()
{
}
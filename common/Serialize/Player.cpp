#include "Player.hh"

Player::Player(const int x, const int y, const int idPlayer)
{
  this->setType(rtype::PLAYER);
  this->setName("");
  this->setPosX(x);
  this->setPosY(y);
  this->setHeight(6);
  this->setWidth(10);
  this->setSpeedX(1);
  this->setSpeedY(1);
  this->setLife(100);
  this->setSpriteRepo("/res/img/ship/spaceShip10.png");
  this->_collisionBox = new CollisionBox(this);
  refresh();
  this->_missileCooldown = 0;
  this->_idPlayer = idPlayer;
}

Player::~Player()
{
}

int			Player::getMissileCooldown() const
{
	return (_missileCooldown);
}

void		Player::setMissileCooldown(const int mC)
{
	_missileCooldown = mC;
}

int			Player::getIdPlayer() const
{
	return (_idPlayer);
}

void		Player::update()
{
}

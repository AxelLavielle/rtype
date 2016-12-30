#include "Player.hh"

Player::Player(const int x, const int y, const int idPlayer)
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
  _collisionBox = new CollisionBox(this);
  refresh();
  _missileCooldown = 0;
  _idPlayer = idPlayer;
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
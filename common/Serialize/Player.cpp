#include "Player.hh"

Player::Player(const int x, const int y, const int idPlayer, const std::string &name)
{
  this->setType(rtype::PLAYER);
  this->setName(name);
  this->setPosX(x);
  this->setPosY(y);
  this->setHeight(6);
  this->setWidth(10);
  this->setSpeedX(1);
  this->setSpeedY(1);
  this->setLife(8);
  this->setAttack(1);
  this->setSpriteRepo("/res/img/ship/spaceShip" + std::to_string(idPlayer) + "0.png");
  this->_collisionBox = new CollisionBox(this);
  refresh();
  this->_missileCooldown = 0;
  this->_idPlayer = idPlayer;
  _nbSuperShoot = 1;
  _nbWave = 0;
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

int Player::getNbSuperShoot() const
{
	return (_nbSuperShoot);
}

void Player::setNbSuperShoot(const int shoot)
{
	_nbSuperShoot = shoot;
}

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
  this->setSpriteRepo("/res/img/ship/spaceShip" + std::to_string(idPlayer) + "0.png");
  this->_collisionBox = new CollisionBox(this);
  refresh();
  this->_missileCooldown = 0;
  this->_idPlayer = idPlayer;
  _nbWave = 0;
}

Player::~Player()
{
}

int			Player::getWaveNumber() const
{
	return (_nbWave);
}

void		Player::setWaveNumber(const int nbWave)
{
	_nbWave = nbWave;
}

int			Player::getScore() const
{
	return (_score);
}

void		Player::setScore(const int score)
{
	_score = score;
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

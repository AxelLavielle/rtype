#include "stdafx.h"
#include "BossMonster.hh"

BossMonster::BossMonster()
{
	this->setType(rtype::MONSTER);
	this->setName("BossMonster");
	this->setPosX(0);
	this->setPosY(0);
	this->setAttack(2);
	this->setHeight(50);
	this->setWidth(35);
	this->setSpeedX(-1);
	this->setSpeedY(0);
	this->setLife(1000);
	_currentSprite = 0;
	this->setSpriteRepo("/res/img/boss/boss" + std::to_string(_currentSprite) + ".png");
	refresh();
	this->_collisionBox = new CollisionBox(this);
}

BossMonster::BossMonster(const int x, const int y)
{
  this->setType(rtype::MONSTER);
  this->setName("BossMonster");
  this->setPosX(x);
  this->setPosY(y);
  this->setHeight(50);
  this->setWidth(35);
  this->setSpeedX(-1);
  this->setSpeedY(0);
  this->setLife(1000);
  _currentSprite = 0;
  this->setSpriteRepo("/res/img/boss/boss" + std::to_string(_currentSprite) + ".png");
  refresh();
  this->_collisionBox = new CollisionBox(this);
}

BossMonster::~BossMonster()
{
}

void		BossMonster::update()
{
	static int	moveX = 0;
	static int	goingUp = true;
	
	if (_currentSprite > 5)
		_currentSprite = 0;
	
	setSpriteRepo("/res/img/boss/boss" + std::to_string(_currentSprite) + ".png");
	setPosX(_posX + _speedX);
	setPosY(_posY + _speedY);
	_currentSprite++;

	moveX++;
	if (_speedX != 0 && moveX > 50)
	{
		setSpeedX(0);
		setSpeedY(-1);
	}
	if (goingUp && _posY < 10)
	{
		setSpeedY(_speedY * (-1));
		goingUp = false;
	}
	else if (!goingUp && _posY + _height > 75)
	{
		setSpeedY(_speedY * (-1));
		goingUp = true;
	}
	refresh();
}

extern "C"
{
	__declspec(dllexport) IEntity	*createEntity()
	{
		return (new BossMonster);
	}
}

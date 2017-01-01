#include "stdafx.h"
#include "RedSpiralMonster.hh"

RedSpiralMonster::RedSpiralMonster()
{
	this->setType(rtype::MONSTER);
	this->setName("RedSpiralMonster");
	this->setAttack(1);
	this->setPosX(0);
	this->setPosY(0);
	this->setHeight(8);
	this->setWidth(8);
	this->setSpeedX(-1);
	this->setSpeedY(1);
	this->setLife(100);
	_currentSprite = 0;
	this->setSpriteRepo("/res/img/redspiral/redspiral" + std::to_string(_currentSprite) + ".png");
	refresh();
	this->_collisionBox = new CollisionBox(this);
}

RedSpiralMonster::RedSpiralMonster(const int x, const int y)
{
  this->setType(rtype::MONSTER);
  this->setName("RedSpiralMonster");
  this->setPosX(x);
  this->setPosY(y);
  this->setHeight(8);
  this->setWidth(8);
  this->setSpeedX(-1);
  this->setSpeedY(1);
  this->setLife(100);
  _currentSprite = 0;
  this->setSpriteRepo("/res/img/redspiral/redspiral" + std::to_string(_currentSprite) + ".png");
  refresh();
  this->_collisionBox = new CollisionBox(this);
}

RedSpiralMonster::~RedSpiralMonster()
{
}

void		RedSpiralMonster::update()
{
	static bool goingUp = true;

	if (_currentSprite > 7)
	{
		_currentSprite = 0;
		if (goingUp)
		{
			goingUp = false;
			setSpeedY(_speedY * (-1));
		}
		else
		{
			goingUp = true;
			setSpeedY(_speedY * (-1));
		}

	}
	setSpriteRepo("/res/img/redspiral/redspiral" + std::to_string(_currentSprite) + ".png");
	setPosX(_posX + _speedX);
	setPosY(_posY + _speedY);
	_currentSprite++;

	refresh();

}


extern "C"
{
	__declspec(dllexport) IEntity	*createEntity()
	{
		return (new RedSpiralMonster);
	}
}

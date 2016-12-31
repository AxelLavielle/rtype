#include "BossMonster.hh"

BossMonster::BossMonster()
{}

BossMonster::BossMonster(const int x, const int y)
{
  this->setType(rtype::MONSTER);
  _name = "BossMonster1";
  this->setName("");
  this->setPosX(x);
  this->setPosY(y);
  this->setHeight(4);
  this->setWidth(4);
  this->setSpeedX(-1);
  this->setSpeedY(1);
  this->setLife(100);
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
	static bool goingUp = true;
	static int	moveX = 0;

	if (_currentSprite > 5)
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
	setSpriteRepo("/res/img/boss/boss" + std::to_string(_currentSprite) + ".png");
	setPosX(_posX + _speedX);
	setPosY(_posY + _speedY);
	_currentSprite++;

	if (moveX > 20)
		setSpeedX(0);
	refresh();
}

//extern "C" IEntity	*createEntity()
//{
//  return (new BossMonster);
//}

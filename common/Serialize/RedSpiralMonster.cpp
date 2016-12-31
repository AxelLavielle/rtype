#include "RedSpiralMonster.hh"

RedSpiralMonster::RedSpiralMonster()
{}

RedSpiralMonster::RedSpiralMonster(const int x, const int y)
{
  this->setType(rtype::MONSTER);
  _name = "RedSpiralMonster1";
  this->setName("");
  this->setPosX(x);
  this->setPosY(y);
  this->setHeight(4);
  this->setWidth(4);
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

//extern "C" IEntity	*createEntity()
//{
//  return (new RedSpiralMonster);
//}

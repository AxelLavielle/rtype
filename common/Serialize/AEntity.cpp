#include "AEntity.hh"

AEntity::AEntity()
{
	static unsigned int	id = 0;

	_posX = -1;
	_posY = -1;
	_type = rtype::ABSTRACT;
	_speedX = -1;
	_speedY = -1;
	_name = "ABSTRACT";
	_spritePath = "";
	_life = -1;
	_height = -1;
	_width = -1;
	_separator = '|';
	_id = id;
	_isDead = false;
	id++;
}

AEntity::~AEntity()
{
}

void			AEntity::setPosX(const double posX)
{
	std::stringstream	ss;

	ss << posX;
	_args += ss.str() + _separator;
	_posX = posX;
}

double			AEntity::getPosX() const
{
	return (_posX);
}

void			AEntity::setPosY(const double posY)
{
	std::stringstream	ss;

	ss << posY;
	_args += ss.str() + _separator;
	_posY = posY;
}

double AEntity::getHeight() const
{
	return (_height);
}

void AEntity::setHeight(const double height)
{
	std::stringstream	ss;

	ss << height;
	_args += ss.str() + _separator;
	_height = height;
}

double AEntity::getWidth() const
{
	return (_width);
}

void AEntity::setWidth(const double width)
{
	std::stringstream	ss;

	ss << width;
	_args += ss.str() + _separator;
	_width = width;
}

void AEntity::setId(const unsigned int id)
{
	std::stringstream	ss;

	ss << id;
	_args += ss.str() + _separator;
	_id = id;
}

unsigned int AEntity::getId() const
{
	return (_id);
}

bool AEntity::isDead() const
{
	return (_isDead);
}

void AEntity::setDead(const bool status)
{
	std::stringstream	ss;

	ss << status;
	_args += ss.str() + _separator;
	_isDead = status;
}

double			AEntity::getPosY() const
{
  return (_posY);
}

void			AEntity::setType(const rtype::EntityType &type)
{
  _type = type;
}

rtype::EntityType	AEntity::getType() const
{
  return (_type);
}

std::string		AEntity::getName() const
{
  return (_name);
}

void			AEntity::setName(const std::string &name)
{
	_args += name + _separator;
	_name = name;
}

void			AEntity::setSpriteRepo(const std::string &path)
{
	_args += path + _separator;
  _spritePath = path;
}

std::string		AEntity::getSpriteRepo() const
{
  return (_spritePath);
}

double			AEntity::getSpeedX() const
{
  return (_speedX);
}

void			AEntity::setSpeedX(const double speedX)
{
	std::stringstream	ss;

	ss << speedX;
	_args += ss.str() + _separator;
	_speedX = speedX;
}

double			AEntity::getSpeedY() const
{
  return (_speedY);
}

void			AEntity::setSpeedY(const double speedY)
{
	std::stringstream	ss;

	ss << speedY;
	_args += ss.str() + _separator;
	_speedY = speedY;
}

int			AEntity::getLife() const
{
  return (_life);
}

void			AEntity::setLife(const int life)
{
	std::stringstream	ss;

	ss << life;
	_args += ss.str() + _separator;
	_life = life;
}

bool AEntity::setArgs(const std::string & args)
{
	std::vector<std::string>				res;

	res = split(args);
	if (res.size() < 8)
		return (false);
	_name = res[0];
	_posX = std::stoi(res[1]);
	_posY = std::stoi(res[2]);
	_height = std::stoi(res[3]);
	_width = std::stoi(res[4]);
	_speedX = std::stoi(res[5]);
	_speedY = std::stoi(res[6]);
	_life = std::stoi(res[7]);
	_spritePath = res[8];
	_args = args;
	return (true);
}

std::string AEntity::getArgs() const
{
	return (_args);
}

void AEntity::refresh()
{
	std::stringstream	ss;

	_args = "";
	_args += _name + _separator;
	ss << _posX;
	_args += ss.str() + _separator; 
	ss.str("");
	ss.clear();
	ss << _posY;
	_args += ss.str() + _separator;
	ss.str("");
	ss.clear();
	ss << _height;
	_args += ss.str() + _separator;
	ss.str("");
	ss.clear();
	ss << _width;
	_args += ss.str() + _separator;
	ss.str("");
	ss.clear();
	ss << _speedX;
	_args += ss.str() + _separator;
	ss.str("");
	ss.clear();
	ss << _speedY;
	_args += ss.str() + _separator;
	ss.str("");
	ss.clear();
	ss << _life;
	_args += ss.str() + _separator;
	_args += _spritePath + _separator;
}

std::vector<std::string>		AEntity::split(const std::string &s)
{
	std::vector<std::string>	elems;
	std::stringstream			ss;
	std::string					item;

	ss.str(s);
	while (std::getline(ss, item, _separator))
	{
		elems.push_back(item);
	}
	return (elems);
}

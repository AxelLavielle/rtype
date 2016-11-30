#include "Player.hh"

Player::Player()
{
}

Player::~Player()
{
}

int		Player::getId(void) const
{
  return (_id);
}

void		Player::setId(const int id)
{
  _id = id;
}

std::string	Player::getName(void) const
{
  return (_name);
}

void		Player::setName(const std::string &name)
{
  _name = name;
}

void		Player::update(void)
{
}

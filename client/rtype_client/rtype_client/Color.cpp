#include "Color.hh"

Color::Color(const int & r, const int & g, const int & b, const int & a)
{
	_r = r;
	_g = g;
	_b = b;
	_a = a;
}

int Color::getR() const
{
	return (_r);
}

int Color::getG() const
{
	return (_g);
}

int Color::getB() const
{
	return (_b);
}

int Color::getA() const
{
	return (_a);
}

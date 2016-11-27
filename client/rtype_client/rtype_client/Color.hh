#pragma once

class Color
{
public:
	Color(const int &r, const int &g, const int &b, const int &a = 255);
	int getR() const;
	int getG() const;
	int getB() const;
	int getA() const;
private:
	int		_r;
	int		_g;
	int		_b;
	int		_a;
};
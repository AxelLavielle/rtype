#pragma once

class Rect
{
public:
	Rect();
	Rect(const int &x, const int &y, const int &height, const int &width);
	Rect(const Rect &r);
	~Rect();
	int getX() const;
	int getY() const;
	int getHeight() const;
	int getWidth() const;
	int setX() const;
	int setY() const;
	int setHeight() const;
	int setWidth() const;
	Rect &operator=(const Rect &r);
private:
	int _x;
	int _y;
	int _height;
	int _width;
};
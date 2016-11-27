#pragma once

class Rect
{
public:
	Rect(const int &x, const int &y, const int &height, const int &width);
	~Rect();
	int getX() const;
	int getY() const;
	int getHeight() const;
	int getWidth() const;
private:
	int _x;
	int _y;
	int _height;
	int _width;
};
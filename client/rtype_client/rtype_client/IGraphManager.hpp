#pragma once

#include <string>
#include "Rect.hh"
#include "Color.hh"

class IGraphManager
{
public:
	virtual ~IGraphManager() {}
	virtual bool init() = 0;
	virtual bool isWindowOpen() = 0;
	virtual void refresh() = 0;
	virtual void close() = 0;
	virtual void setWinHeight(const int &height) = 0;
	virtual void setWinWidth(const int &width) = 0;
	virtual bool setBackground(const std::string &imagePath) = 0;
	virtual bool drawRectangle(const std::string & spritePath, const Rect & rect) = 0;
	virtual bool drawText(const std::string & text, const int & posX, const int & posY, const int &size, const Color &color, const std::string & font = "../../res/font/Aerospace.ttf") = 0;
	virtual void clearWindow() = 0;
};


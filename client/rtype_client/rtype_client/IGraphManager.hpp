#pragma once

#include <string>

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
};


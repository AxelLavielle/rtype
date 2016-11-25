#pragma once

#include "IGraphManager.hpp"

class AGraphManager : public IGraphManager
{
public:
	AGraphManager();
	virtual ~AGraphManager();
	virtual bool init() = 0;
	virtual bool isWindowOpen() = 0;
	virtual void refresh() = 0;
	virtual void close() = 0;
	virtual void setWinHeight(const int &height);
	virtual void setWinWidth(const int &width);
	virtual bool setBackground(const std::string &imagePath) = 0;
protected:
	int			_winX;
	int			_winY;
};


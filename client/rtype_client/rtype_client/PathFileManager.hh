#pragma once

#include <string>
#include <stdlib.h>

class PathFileManager
{
public:
	PathFileManager();
	~PathFileManager();
	bool init();
	std::string getRoot() const;
private:
	std::string			_root;
};


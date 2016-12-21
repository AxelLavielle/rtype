#pragma once

#include <string>
#include <stdlib.h>

class PathFileManager
{
public:
	PathFileManager();
	PathFileManager(const PathFileManager &p);
	~PathFileManager();
	bool init();
	std::string getRoot() const;
	PathFileManager &operator=(const PathFileManager &p);
private:
	std::string			_root;
};

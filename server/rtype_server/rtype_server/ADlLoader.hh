#pragma once

#include "IDlLoader.hpp"

class ADlLoader : public IDlLoader
{
public:
	ADlLoader();
	virtual		~ADlLoader();
	IEntity		getInstance();
	bool		load(const std::string &path);
private:
	std::string	_dlPath;
};

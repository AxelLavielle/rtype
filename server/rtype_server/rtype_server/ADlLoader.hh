#pragma once

#include "IDlLoader.hpp"

class ADlLoader : public IDlLoader
{
public:
	ADlLoader();
	virtual			~ADlLoader();
	virtual IEntity		*getInstance();
	virtual bool		load(const std::string &path);
private:
	std::string		_dlPath;
};

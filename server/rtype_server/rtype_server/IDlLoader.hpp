#pragma once

#include <string>
#include "IEntity.hpp"

class IDlLoader
{
public:
	virtual ~IDlLoader() {}
	virtual IEntity	*getInstance() = 0;
	virtual bool load(const std::string &path) = 0;
};

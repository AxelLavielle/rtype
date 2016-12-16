#pragma once

#include "IMapGenerator.hpp"

class AMapGenerator : public IMapGenerator
{
public:
	AMapGenerator();
	~AMapGenerator();

	virtual void generator() = 0;
};


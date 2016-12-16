#pragma once
#pragma once

# include "Map.hh"

class				IMapGenerator
{
public:
	virtual ~IMapGenerator() {}

	virtual Map		generate() = 0;
};

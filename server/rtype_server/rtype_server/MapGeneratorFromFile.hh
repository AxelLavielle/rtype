#pragma once

#include "AMapGenerator.hh"
#include <iostream>
#include <fstream>
#include "Barrier.hh"
#include "Player.hh"
#include "PowerUp.hh"
#include "Monster.hh"

class			MapGeneratorFromFile : public AMapGenerator
{
public:
	MapGeneratorFromFile();
	~MapGeneratorFromFile();

	Map			generate(const std::string &);
};


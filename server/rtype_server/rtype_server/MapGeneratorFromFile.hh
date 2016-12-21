#pragma once

#include "Map.hh"
#include <iostream>
#include <fstream>
#include "Barrier.hh"
#include "Player.hh"
#include "PowerUp.hh"
#include "Monster.hh"

class			        MapGenerator
{
public:
	static Map		generate();
	static Map		generate(const std::string &);
};


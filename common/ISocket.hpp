#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "MemTools.hh"

class				ISocket
{
public:
	virtual ~ISocket() {}
	
	virtual bool	init(const std::string &, int) = 0;
	virtual bool	closure() = 0;
};


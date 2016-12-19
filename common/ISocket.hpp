#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "MemTools.hh"

class				ISocket
{
public:
	virtual ~ISocket() {}
	
	virtual bool	init(const std::string &, const int) = 0;
	virtual bool	closure() = 0;
};


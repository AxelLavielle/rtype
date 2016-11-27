#pragma once

#include <windows.h>
#include <iostream>
#include <string>
#include <stdio.h>

class				ISocket
{
public:
	virtual ~ISocket() {}
	
	virtual bool	init(const std::string &, int) = 0;
	virtual bool	sendData(const char *) = 0;
	virtual char	*receiveData() = 0;
	virtual bool	close() = 0;
};


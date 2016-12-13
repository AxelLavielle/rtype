#pragma once

#include <iostream>
#include <string>

class				ISocket
{
public:
	virtual ~ISocket() {}
	
	virtual bool	init(const std::string &, int) = 0;
	virtual bool	sendData(const char *) = 0;
	virtual char	*receiveData() = 0;
	//virtual bool	connectToServer() = 0;
	virtual bool	close() = 0;
};


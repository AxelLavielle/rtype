#pragma once

# include <iostream>
# include <string>

class				ISocket
{
public:
	ISocket();
	virtual ~ISocket();
	
	virtual bool	init(const std::string &, int) = 0;
	virtual bool	send(const char *) = 0;
	virtual char	*receive() = 0;
	virtual bool	close() = 0;
};


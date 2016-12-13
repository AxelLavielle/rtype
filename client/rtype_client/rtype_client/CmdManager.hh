#pragma once

#include <string>
#include "SocketClientTCP.hh"

class CmdManager
{
public:
	CmdManager();
	~CmdManager();
	bool newCmd(const std::string & cmd);
};


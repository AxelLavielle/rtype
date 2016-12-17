#pragma once

#include	<vector>
#include	<sstream>
#include "ACommand.hh"

class BasicCmd :
	public ACommand
{
public:
	BasicCmd();
	virtual ~BasicCmd();
	virtual void				setCommandArg(const std::string & arg);
	std::string					getArg(const int index) const;
	std::vector<std::string>	getAllArg() const;
	void						addArg(const std::string & str);

	std::vector<std::string>	split(const std::string & s);

private:
	std::vector<std::string>	_argList;
};


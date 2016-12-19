#pragma once

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
	void						addArg(const std::string &str);

private:
	std::vector<std::string>	_argList;
};


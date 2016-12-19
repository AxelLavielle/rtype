#pragma once

#include	<string>
#include	<vector>
#include	<sstream>
#include	"ICommand.hpp"

class		ACommand : public ICommand
{
public:
  ACommand();
  virtual	~ACommand();

  virtual CmdName			getCommandName() const;
  virtual const std::string	getCommandArg() const;
  virtual void				setCommandArg(const std::string &);
  virtual void				setCommandType(CmdType type);
  virtual CmdType			getCommandType() const;

protected:
  CmdType		_cmdType;
  CmdName		_cmdName;
  std::string	_arg;
  char			_separator;

  std::vector<std::string>	split(const std::string &);

};

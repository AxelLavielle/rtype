#pragma once

#include	"ACommand.hh"

class		InputCmd : public ACommand
{
public:
  InputCmd();
  virtual	~InputCmd();

  virtual CmdName		getCommandName() const;
  std::string			getKey() const;
  void					setKey(const std::string &key);
  virtual void				setCommandArg(const std::string &);

private:
	std::string			_key;
};

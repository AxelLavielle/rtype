#pragma once

#include	"ACommand.hh"
#include	<iostream>

typedef std::pair<std::string, bool>	PlayerInfo;

struct		RoomInfoCmd : public ACommand
{
public:
  RoomInfoCmd();
  virtual	~RoomInfoCmd();

  void				setName(const std::string &);
  void				addPlayer(const std::string &, const bool);
  CmdName			getCommandName() const;
  const std::string	getCommandArg() const;
  const std::string	getName() const;
  std::vector<PlayerInfo>	getPlayersList() const;


private:
  std::string				_arg;
  std::string				_name;
  std::vector<PlayerInfo>	_playersList;
};

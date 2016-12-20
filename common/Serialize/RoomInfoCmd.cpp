#include	"RoomInfoCmd.hh"

RoomInfoCmd::RoomInfoCmd()
{
	_cmdName = ROOM_INFO;
}

RoomInfoCmd::~RoomInfoCmd()
{
}

void	RoomInfoCmd::setName(const std::string &name)
{
	_name = name;
	_arg += name + _separator;
}

void	RoomInfoCmd::addPlayer(const std::string &pName, const bool pStatus)
{
	_playersList.push_back(std::make_pair(pName, pStatus));
	_arg += pName + _separator + std::to_string(pStatus) + _separator;
}

CmdName			RoomInfoCmd::getCommandName() const
{
	return (_cmdName);
}

const std::string	RoomInfoCmd::getCommandArg() const
{
	std::cout << "[RoomInfo] : ARG = {" << _arg << "}" << std::endl;
	return (_arg);
}

const std::string	RoomInfoCmd::getName() const
{
	return (_name);
}

std::vector<PlayerInfo>	RoomInfoCmd::getPlayersList() const
{
	return (_playersList);
}
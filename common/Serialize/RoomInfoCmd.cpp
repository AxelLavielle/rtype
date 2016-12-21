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

void RoomInfoCmd::setCommandArg(const std::string &arg)
{
	std::stringstream			ss;
	std::string					item;
	int							i;
	PlayerInfo					pl;
	bool						first;

	first = true;
	std::cout << "set command args" << std::endl;
	ss.str(arg);
	i = 0;
	while (std::getline(ss, item, _separator))
	{
		if (first)
		{
			_name = item;
			first = false;
			break;
		}
		std::cout << "i = " << i << std::endl;
		if (i == 0)
			pl.first = item;
		else if (i == 1)
		{
			std::cout << "item = " << item << std::endl;
			pl.second = std::stoi(item);
			_playersList.push_back(pl);
		}
		i++;
		i = i % 2;
	}
	_arg = arg;
}

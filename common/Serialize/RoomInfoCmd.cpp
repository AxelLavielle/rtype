#include	"RoomInfoCmd.hh"

RoomInfoCmd::RoomInfoCmd()
{
	_cmdName = ROOM_INFO;
	_name = "";
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
	std::cout << arg << std::endl;
	while (std::getline(ss, item, _separator))
	{
		if (first)
		{
			_name = item;
			first = false;
		}
		else
		{
			if (i == 0)
				pl.first = item;
			else if (i == 1)
			{
				pl.second = std::stoi(item);
				_playersList.push_back(pl);
			}
			i++;
		}
		if (i >= 2)
			i = 0;
	}
	_arg = arg;
}

#include	"ListRoomCmd.hh"

ListRoomCmd::ListRoomCmd()
{

}

ListRoomCmd::~ListRoomCmd()
{
}

void	ListRoomCmd::addRoom(const std::string &name, const int nbPlayers)
{
	_roomList.push_back(std::make_pair(name, nbPlayers));
	_arg += name + _separator + std::to_string(nbPlayers) + _separator;
}

void									ListRoomCmd::setCommandArg(const std::string &arg)
{
	std::vector<std::string>			vectString;
	std::vector<std::string>::iterator	it;

	_arg = arg;
	vectString = split(arg);
	it = vectString.begin();
	while (it != vectString.end())
	{
		if (it + 1 != vectString.end())
		{
			_roomList.push_back(std::make_pair((*it), std::stoi(*(it +1))));
		}
		it += 2;
	}
}

CmdName			ListRoomCmd::getCommandName() const
{
  return (ROOM_LIST);
}
#include <iostream>

const std::string	ListRoomCmd::getCommandArg() const
{
	std::cout << "[ListRoomCmd] : ARG = {" << _arg << "}" << std::endl;
	return (_arg);
}

std::pair<std::string, int>	ListRoomCmd::getRoom(const int index) const
{
	return (_roomList.at(index));
}

std::vector<std::pair<std::string, int>> ListRoomCmd::getAllRooms() const
{
	return (_roomList);
}

#include	"ListRoomCmd.hh"

ListRoomCmd::ListRoomCmd()
{

}

ListRoomCmd::~ListRoomCmd()
{
}

void				ListRoomCmd::addRoom(const int idRoom, const std::string &name, const int nbPlayers)
{
	RoomNameNbPlayer namePlayer;
	RoomIdInfos		idInfos;

	namePlayer = std::make_pair(name, nbPlayers);
	idInfos = std::make_pair(idRoom, namePlayer);
	_roomList.push_back(idInfos);
	_arg += std::to_string(idRoom) + _separator
			+ name + _separator
			+ std::to_string(nbPlayers) + _separator;
}

void									ListRoomCmd::setCommandArg(const std::string &arg)
{
	std::vector<std::string>			vectString;
	std::vector<std::string>::iterator	it;
	RoomNameNbPlayer namePlayer;
	RoomIdInfos		idInfos;

	_arg = arg;
	vectString = split(arg);
	it = vectString.begin();
	while (it != vectString.end())
	{
		if (it + 2 != vectString.end())
		{
			namePlayer = std::make_pair((*(it + 1)), std::stoi((*(it + 2))));
			idInfos = std::make_pair(std::stoi((*it)), namePlayer);
			_roomList.push_back(idInfos);
		}
		it += 3;
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

RoomIdInfos					ListRoomCmd::getRoom(const int index) const
{
	return (_roomList.at(index));
}

std::vector<RoomIdInfos>	ListRoomCmd::getAllRooms() const
{
	return (_roomList);
}

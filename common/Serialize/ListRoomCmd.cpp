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
#include <iostream>

void									ListRoomCmd::setCommandArg(const std::string &arg)
{
	std::vector<std::string>			vectString;
	RoomNameNbPlayer namePlayer;
	RoomIdInfos		idInfos;
	unsigned int						i;

	i = 0;
	_arg = arg;
	vectString = split(arg);
	while (i < vectString.size())
	{
		if (i + 2 != vectString.size())
		{
			namePlayer = std::make_pair((vectString[i + 1]), std::stoi((vectString[i + 2])));
			idInfos = std::make_pair(std::stoi(vectString[i]), namePlayer);
			_roomList.push_back(idInfos);
		}
		i += 3;
	}
	std::cout << this <<" DANS LA FUNCTION = " << _roomList.size() << std::endl;
}

CmdName			ListRoomCmd::getCommandName() const
{
  return (ROOM_LIST);
}

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
	std::cout << this << " DANS LE GETTEUR = " << _roomList.size() << std::endl;
	return (_roomList);
}

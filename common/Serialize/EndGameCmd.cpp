#include "EndGameCmd.hh"



EndGameCmd::EndGameCmd()
{
	_arg = "";
}


EndGameCmd::~EndGameCmd()
{
}

void			EndGameCmd::addPlayer(const std::string &name, const int score)
{
	_arg += name + _separator + std::to_string(score) + _separator;
	_player.push_back(std::make_pair(name, score));
}

std::vector<std::pair<std::string, int> >

const std::string	EndGameCmd::getCommandArg() const
{
	return (_arg);
}

void EndGameCmd::setCommandArg(const std::string &arg)
{
	std::stringstream			ss;
	std::string					item;
	int							i;
	std::pair<std::string, int>	pl;

	ss.str(arg);
	i = 0;
	while (std::getline(ss, item, _separator))
	{
		if (i == 0)
			pl.first = item;
		else if (i == 1)
		{
			pl.second = std::stoi(item);
			_player.push_back(pl);
		}
		i++;
	if (i >= 2)
		i = 0;
	}
	_arg = arg;
}
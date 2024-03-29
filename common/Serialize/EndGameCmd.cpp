#include "EndGameCmd.hh"


EndGameCmd::EndGameCmd()
{
	_arg = "";
	_isVictory = false;
	_nbWave = 0;
	_cmdName = END_GAME;
}

EndGameCmd::~EndGameCmd()
{
}

bool			EndGameCmd::getVictory() const
{
	return (_isVictory);
}

int				EndGameCmd::getWaveNumber() const
{
	return (_nbWave);
}

void			EndGameCmd::addPlayer(const std::string &name, const int score)
{
	_player.push_back(std::make_pair(name, score));
       	_arg += name + _separator + std::to_string(score) + _separator;
}

void		EndGameCmd::setVictory(const bool victory)
{
	_isVictory = victory;
	_arg += std::to_string(static_cast<int>(_isVictory)) + _separator;
}

void	EndGameCmd::setWaveNumber(const int wave)
{
	_nbWave = wave;
	_arg += std::to_string(_nbWave) + _separator;
}

std::vector<std::pair<std::string, int> >		EndGameCmd::getPlayerList() const
{
	return (_player);
}	

void	EndGameCmd::parsePlayer()
{
	std::vector<std::pair<std::string, int> >::iterator		it;

	it = _player.begin();
	while (it != _player.end())
	{
		_arg += it->first + _separator + std::to_string(it->second) + _separator;
		++it;
	}
}

const std::string	EndGameCmd::getCommandArg()
{
	// _arg += std::to_string(static_cast<int>(_isVictory)) + _separator;
	// _arg += std::to_string(_nbWave) + _separator;
	// parsePlayer();
	return (_arg);
}
//#include <iostream>
void EndGameCmd::setCommandArg(const std::string &arg)
{
	std::stringstream			ss;
	std::string					item;
	int							i;
	int							j;
	std::pair<std::string, int>	pl;

	//std::cout << "ARGUMENTS = " << arg << std::endl;
	//std::cout << "size PLAYER = " << _player.size()  << std::endl;
	ss.str(arg);
	i = 0;
	j = 0;
	while (std::getline(ss, item, _separator))
	{
		if (j == 0)
			_isVictory = static_cast<bool>(std::stoi(item));
		else if (j == 1)
			_nbWave = std::stoi(item);
		if (j > 1)
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
		j++;
	}
	_arg = arg;
}

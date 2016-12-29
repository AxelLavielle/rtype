#include "SaveConfig.hh"

SaveConfig::SaveConfig()
{
	_playerName = "player";
	_up = "z";
	_down = "s";
	_right = "d";
	_left = "q";
	_pew = "k";
	_music = 50;
	_sfx = 50;
	_iport = "10.16.252.95:42000";
}

SaveConfig::SaveConfig(const std::string &playerName, const std::string &up, const std::string &down, const std::string &right, const std::string &left, const std::string &pew, const int music, const int sfx, const std::string &iport)
{
	_playerName = playerName;
	_up = up;
	_down = down;
	_right = right;
	_left = left;
	_pew = pew;
	_music = music;
	_sfx = sfx;
	_iport = iport;
}

SaveConfig::~SaveConfig()
{
}

void			SaveConfig::writeToFile()
{
	std::fstream		fileStream;

	fileStream.open(".menuConfig.xml",
		std::fstream::in |
		std::fstream::out |
		std::fstream::trunc);
	if (fileStream.is_open())
	{
		fileStream << "<Menu Config>\n";

		fileStream << "<PlayerName>" << _playerName << "</PlayerName>" << std::endl;
		fileStream << "<Up>" << _up << "</Up>" << std::endl;
		fileStream << "<Down>" << _down << "</Down>" << std::endl;
		fileStream << "<Right>" << _right << "</Right>" << std::endl;
		fileStream << "<Left>" << _left << "</Left>" << std::endl;
		fileStream << "<Pew>" << _pew << "</Pew>" << std::endl;
		fileStream << "<Music>" << _music << "</Music>" << std::endl;
		fileStream << "<SFX>" << _sfx << "</SFX>" << std::endl;
		fileStream << "<Iport>" << _iport << "</Iport>" << std::endl;

		fileStream << "</Menu Config>\n" << std::endl;
	}
	else
		std::cerr << "Error: Menu File Failed to Open!" << std::endl;

	fileStream.close();
}

void				SaveConfig::needleInHaystack(const std::string &haystack)
{
	// ifs to replace with a dual tab string tab and var adress tab on a single if
	if (haystack.find("<PlayerName>") != std::string::npos && haystack.find("</PlayerName>") != std::string::npos)
	{
		std::istringstream ss(haystack.substr(haystack.find("<PlayerName>") + 12, haystack.find("</PlayerName>") - 12));
		ss >> _playerName;
	}
	if (haystack.find("<Up>") != std::string::npos && haystack.find("</Up>") != std::string::npos)
	{
		std::istringstream ss(haystack.substr(haystack.find("<Up>") + 4, haystack.find("</Up>") - 4));
		ss >> _up;
	}
	if (haystack.find("<Down>") != std::string::npos && haystack.find("</Down>") != std::string::npos)
	{
		std::istringstream ss(haystack.substr(haystack.find("<Down>") + 6, haystack.find("</Down>") - 6));
		ss >> _down;
	}
	if (haystack.find("<Right>") != std::string::npos && haystack.find("</Right>") != std::string::npos)
	{
		std::istringstream ss(haystack.substr(haystack.find("<Right>") + 7, haystack.find("</Right>") - 7));
		ss >> _right;
	}
	if (haystack.find("<Left>") != std::string::npos && haystack.find("</Left>") != std::string::npos)
	{
		std::istringstream ss(haystack.substr(haystack.find("<Left>") + 6, haystack.find("</Left>") - 6));
		ss >> _left;
	}
	if (haystack.find("<Pew>") != std::string::npos && haystack.find("</Pew>") != std::string::npos)
	{
		std::istringstream ss(haystack.substr(haystack.find("<Pew>") + 5, haystack.find("</Pew>") - 5));
		ss >> _pew;
	}
	if (haystack.find("<Music>") != std::string::npos && haystack.find("</Music>") != std::string::npos)
	{
		std::istringstream ss(haystack.substr(haystack.find("<Music>") + 7,	haystack.find("</Music>")));
		ss >> _music;
	}
	if (haystack.find("<SFX>") != std::string::npos	&& haystack.find("</SFX>") != std::string::npos)
	{
		std::istringstream ss(haystack.substr(haystack.find("<SFX>") + 5, haystack.find("</SFX>")));
		ss >> _sfx;
	}
	if (haystack.find("<Iport>") != std::string::npos && haystack.find("</Iport>") != std::string::npos)
	{
		std::istringstream ss(haystack.substr(haystack.find("<Iport>") + 7, haystack.find("</Iport>") - 7));
		ss >> _iport;
	}
}

void				SaveConfig::readFromFile()
{
	std::fstream			fileStream;

	fileStream.open(".menuConfig.xml", std::fstream::in | std::fstream::binary | std::fstream::out);
	if (fileStream.is_open())
	{
		std::string line;

		while (getline(fileStream, line))
			needleInHaystack(line);
	}
	else
		std::cerr << "Error: Menu File Failed to Open!1" << std::endl;
	fileStream.close();
}

std::string		SaveConfig::getPlayerName() const
{
	return (_playerName);
}

void			SaveConfig::setPlayerName(const std::string &playerName)
{
	_playerName = playerName;
}

std::string		SaveConfig::getUp() const
{
	return (_up);
}

void			SaveConfig::setUp(const std::string &up)
{
	_up = up;
}

std::string		SaveConfig::getDown() const
{
	return (_down);
}

void			SaveConfig::setDown(const std::string &down)
{
	_down = down;
}

std::string		SaveConfig::getRight() const
{
	return (_right);
}

void			SaveConfig::setRight(const std::string &right)
{
	_right = right;
}

std::string		SaveConfig::getLeft() const
{
	return (_left);
}

void			SaveConfig::setLeft(const std::string &left)
{
	_left = left;
}

std::string		SaveConfig::getPew() const
{
	return (_pew);
}

void			SaveConfig::setPew(const std::string &pew)
{
	_pew = pew;
}

int				SaveConfig::getMusic() const
{
  return (_music);
}

void			SaveConfig::setMusic(const int music)
{
  _music = music;
}

int				SaveConfig::getSfx() const
{
  return (_sfx);
}

void			SaveConfig::setSfx(const int sfx)
{
  _sfx = sfx;
}

std::string		SaveConfig::getIport() const
{
	return (_iport);
}

void			SaveConfig::setIport(const std::string &iport)
{
	_iport = iport;
}

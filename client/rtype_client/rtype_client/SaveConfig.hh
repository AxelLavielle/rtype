#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

class SaveConfig
{
public:
	SaveConfig();
	SaveConfig(const std::string &, const std::string &, const std::string &, const std::string &, const std::string &, const std::string &, const std::string &, const int, const int, const std::string &);
	~SaveConfig();
	void	writeToFile();
	void	readFromFile();

	std::string	getPlayerName() const;
	void		setPlayerName(const std::string &);
	std::string	getUp() const;
	void		setUp(const std::string &);
	std::string	getDown() const;
	void		setDown(const std::string &);
	std::string	getRight() const;
	void		setRight(const std::string &);
	std::string	getLeft() const;
	void		setLeft(const std::string &);
	std::string	getPew() const;
	void		setPew(const std::string &);
	std::string	getSuperPew() const;
	void		setSuperPew(const std::string &);
	int			getMusic() const;
	void		setMusic(const int);
	int			getSfx() const;
	void		setSfx(const int);
	std::string	getIport() const;
	void		setIport(const std::string &);

private:
	std::string	_playerName;
	std::string _up;
	std::string _down;
	std::string _right;
	std::string _left;
	std::string _pew;
	std::string _superPew;
	int			_music;
	int			_sfx;
	std::string _iport;
	void    needleInHaystack(const std::string &);
};

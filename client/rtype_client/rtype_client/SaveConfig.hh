#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

class SaveConfig
{
private:
	std::string	_player;
	int	_general;
	int	_music;
	int	_sfx;
	int	_level;
	int	_shipModel;
public:
	SaveConfig();
	SaveConfig(const int, const int, const int, const int, const int, const std::string &);
	~SaveConfig();
	void	writeToFile();
	void	readFromFile();
	void  needleInHaystack(const std::string &);

	std::string	getPlayer() const;
	void		setPlayer(const std::string &);
	int		getGeneral() const;
        void		setGeneral(const int);
	int		getMusic() const;
	void		setMusic(const int);
	int		getSfx() const;
	void		setSfx(const int);
	int		getLevel() const;
	void		setLevel(const int);
	int		getShipModel() const;
	void		setShipModel(const int);
};

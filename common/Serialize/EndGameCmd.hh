#pragma once

#include "ACommand.hh"

class EndGameCmd :public ACommand
{
public:
	EndGameCmd();
	virtual ~EndGameCmd();
	bool getVictory() const;
	int getWaveNumber() const;
	void addPlayer(const std::string & name, const int score);
	void setVictory(const bool victory);
	void setWaveNumber(const int wave);
	virtual const std::string getCommandArg();
	virtual void setCommandArg(const std::string & arg);
	std::vector<std::pair<std::string, int> >		getPlayerList() const;


private:
	std::vector<std::pair<std::string, int> >		_player;
	bool											_isVictory;
	int												_nbWave;

	void parsePlayer();
};


#pragma once
#include "C:\rtype\common\Serialize\ACommand.hh"
class EndGameCmd :
	public ACommand
{
public:
	EndGameCmd();
	virtual ~EndGameCmd();
	void addPlayer(const std::string & name, const int score);
	virtual const std::string getCommandArg() const;
	virtual void setCommandArg(const std::string & arg);

private:
	std::vector<std::pair<std::string, int> >		_player;
};


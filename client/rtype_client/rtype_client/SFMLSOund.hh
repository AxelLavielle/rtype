#pragma once

#include <map>
#include <SFML/Audio.hpp>
#include "ASoundManager.hh"

class SFMLSound :
	public ASoundManager
{
public:
	SFMLSound();
	virtual ~SFMLSound();
	virtual bool init();
	virtual bool play(const Sound & sound);
	virtual bool stop(const Sound & sound);
	virtual bool pause(const Sound & sound);
	virtual bool setVolume(const int) const;
	virtual bool setMusicVolume(const int) const;
	virtual bool setSoundVolume(const int) const;
private:
	std::map<sf::Sound*, std::string >		_sound;
	std::map<sf::Music*, std::string >		_music;

	sf::Sound *getSound(const std::string & path) const;
	sf::Music *getMusic(const std::string & path) const;
};


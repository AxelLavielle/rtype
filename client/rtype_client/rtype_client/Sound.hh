#pragma once

#include <string>

class Sound
{
public:
	Sound();
	Sound(const int duration, const std::string & path);
	~Sound();
	void setDuration(const int duration);
	void setFilePath(const std::string & path);
	int getDuration() const;
	std::string getFilePath() const;
	void setMusic(const bool flag);
	bool isMusic() const;
private:
	std::string		_filePath;
	int				_duration;
	bool			_isMusic;
};


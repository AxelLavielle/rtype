#pragma once

# include "Client.hh"

class Room
{
public:
	Room(int);
	Room(int, const std::string &);
	~Room();

	std::string		getName() const;
	void			setName(const std::string &);
	int				getId() const;
	void			pauseGame();
	bool			addClient(const Client &);

private:
	std::string				_name;
	int						_id;
	std::vector<Client>		_clients;
	unsigned int			_nbPlayer;
};


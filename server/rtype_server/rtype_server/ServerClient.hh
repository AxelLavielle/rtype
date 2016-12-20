#pragma once

#define HEADER_SIZE		(4)
#define TCP_PACKET_SIZE (65471)
#define UDP_PACKET_SIZE (1452)
#define DEBUG_MSG (true)

#include "MemTools.hh"
#include <vector>
#include <iostream>
#include <string>

class Room;

class ServerClient
{
private:
	int					_TCPSocketFd;
	char				_sendDataTCP[TCP_PACKET_SIZE];
	int					_lenDataTCP;
	bool				_isDisconnectedTCP;

	char				_sendDataUDP[UDP_PACKET_SIZE];
	int					_lenDataUDP;
	struct sockaddr_in	*_clientAddrUDP;

	bool				_readyStatus;
	bool				_logState;
	int					_currentRoomId;
	std::string			_playerName;

public:
	ServerClient(const int);
	~ServerClient();

	int					getTCPSocket() const;
	void				addTCPDataToSend(const char *, const int);
	const char			*getSendDataTCP() const;
	void				resetDataTCP();
	int					getDataLenTCP() const;
	bool				isDisconnectedTCP() const;
	void				setDisconnectedTCP(const bool);

	struct sockaddr_in	*getAddrUDP() const;
	void				addUDPDataToSend(const char *, const int);
	const char			*getSendDataUDP() const;
	void				resetDataUDP();
	int					getDataLenUDP() const;
	void				setAddrUDP(struct sockaddr_in *);
	void				resetAddrUDP();
	
	void				setCurrentRoom(const int);
	int					getCurrentRoom() const;

	void				setLogged(const bool);
	bool				isLogged() const;

	void				setPlayerName(const std::string &);
	std::string			getPlayerName() const;

	void				setStatus(const bool);
	bool				isReady() const;

};


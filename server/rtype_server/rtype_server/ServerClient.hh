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
	char				_sendData[TCP_PACKET_SIZE];
	int					_lenData;
	bool				_isDisconnectedTCP;
	int					_currentRoomId;
	std::string			_playerName;
	int					_UDPSocketFd;
	char				_sendDataUDP[UDP_PACKET_SIZE];
	int					_lenDataUDP;
	struct sockaddr_in	*_clientAddr;	
	bool				_isDisconnectedUDP;

	bool				_logState;

public:
	ServerClient(int);
	~ServerClient();

	int					getTCPSocket() const;
	void				addDataToSend(const char *, const int);
	const char			*getSendData() const;
	void				resetData();
	int					getDataLen() const;
	
	int					getUDPSocket() const;
	void				addUDPDataToSend(const char *, const int);
	const char			*getSendDataUDP() const;
	void				resetDataUDP();
	int					getDataLenUDP() const;
	struct sockaddr_in	*getAddrUDP() const;
	void				resetUDPSocket();
	
	bool				isDisconnectedTCP() const;
	bool				isDisconnectedUDP() const;
	void				setDisconnectedTCP(const bool);
	void				setDisconnectedUDP(const bool);

	void				setCurrentRoom(const int);
	int					getCurrentRoom() const;

	void				setLogged(const bool);
	bool				isLogged() const;

	void				setPlayerName(const std::string &);
	std::string			getPlayerName() const;
};


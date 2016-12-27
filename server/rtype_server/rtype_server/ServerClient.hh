#pragma once

#define HEADER_SIZE		(4)
#define TCP_PACKET_SIZE (65471)
#define UDP_PACKET_SIZE (1452)
#define DEBUG_MSG (true)

#include "SocketAddress.hh"
#include "MemTools.hh"
#include "InputCmd.hh"
#include "Player.hh"
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

	char				_sendDataUDP[TCP_PACKET_SIZE];
	int					_lenDataUDP;
	SocketAddress		*_clientAddr;

	bool				_readyStatus;
	bool				_logState;
	int					_currentRoomId;
	std::string			_playerName;
	IEntity				*_player;

	std::vector<InputCmd>	_inputs;

public:
	ServerClient(const int, SocketAddress *);
	~ServerClient();

	int					getTCPSocket() const;
	void				addTCPDataToSend(const char *);
	const char			*getSendDataTCP() const;
	void				resetDataTCP();
	int					getDataLenTCP() const;
	bool				isDisconnectedTCP() const;
	void				setDisconnectedTCP(const bool);

	SocketAddress		getAddr() const;
	void				addUDPDataToSend(const char *);
	const char			*getSendDataUDP() const;
	void				resetDataUDP();
	int					getDataLenUDP() const;
	
	void				setCurrentRoom(const int);
	int					getCurrentRoom() const;

	void				setLogged(const bool);
	bool				isLogged() const;

	void				setPlayerName(const std::string &);
	std::string			getPlayerName() const;

	void				setStatus(const bool);
	bool				isReady() const;

	void				addInput(const InputCmd &);
	std::vector<InputCmd>	getInputs() const;
	void				clearInput();

	void				setPlayer(IEntity *player);
	IEntity				*getPlayer() const;
};


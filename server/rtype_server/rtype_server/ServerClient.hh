#pragma once

#include <iostream>
#include <string>
#include "MemTools.hh"

#define HEADER_SIZE		(4)
#define TCP_PACKET_SIZE (65471)
#define UDP_PACKET_SIZE (1452)
#define DEBUG_MSG (true)

class ServerClient
{
private:
	int					_TCPSocketFd;
	char				_sendData[TCP_PACKET_SIZE];
	int					_lenData;
	
	int					_UDPSocketFd;
	char				_sendDataUDP[UDP_PACKET_SIZE];
	int					_lenDataUDP;
	struct sockaddr_in	_clientAddr;
	
	bool		_isDisconnected;

public:
	ServerClient(int);
	~ServerClient();

	int					getTCPSocket() const;
	void				addDataToSend(const char *, int);
	const char			*getSendData() const;
	void				resetData();
	int					getDataLen() const;

	int					getUDPSocket() const;
	void				addUDPDataToSend(const char *, int);
	const char			*getSendDataUDP() const;
	void				resetDataUDP();
	int					getDataLenUDP() const;
	struct sockaddr_in	*getAddrUDP() const;
	
	bool				isDisconnected() const;
	void				setDisconnected(bool);
};


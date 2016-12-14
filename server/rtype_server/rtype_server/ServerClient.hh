#pragma once

#include <iostream>
#include <string>
#include "MemTools.hh"

#define HEADER_SIZE		(4)
#define TCP_PACKET_SIZE (65471)
#define DEBUG_MSG (true)

class ServerClient
{
private:
	int			_TCPSocketFd;
	char		_sendData[TCP_PACKET_SIZE];
	int			_lenData;
	bool		_isDisconnected;

public:
	ServerClient(int);
	~ServerClient();

	int			getTCPSocket() const;
	void		addDataToSend(const char *, int);
	const char	*getSendData() const;
	void		resetData();
	int			getDataLen() const;
	bool		isDisconnected() const;
	void		setDisconnected(bool);
};


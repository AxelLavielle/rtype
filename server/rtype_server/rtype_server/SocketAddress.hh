#pragma once

#ifdef _WIN32

# include <winsock2.h>
# include <ws2tcpip.h>
# include <windows.h>
# pragma comment(lib, "Ws2_32.lib")

#elif __linux__

# include <sys/select.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <unistd.h>
# include <stdio.h>
# include <netdb.h>

#endif

class SocketAddress
{
private:
	struct in_addr		_addr;

public:
	SocketAddress(struct in_addr);
	~SocketAddress();

	struct in_addr getAddr() const;
};


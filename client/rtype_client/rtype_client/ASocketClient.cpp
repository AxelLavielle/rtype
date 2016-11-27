#include "ASocketClient.hh"

ASocketClient::ASocketClient()
{

}


ASocketClient::~ASocketClient()
{

}

bool			ASocketClient::close()
{
	int			iResult;

	iResult = shutdown(_connectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR)
	{
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(_connectSocket);
		WSACleanup();
		return 1;
	}
}

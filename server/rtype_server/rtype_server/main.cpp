
#include "SocketServerTCP.hh"
#include <vector>

int main()
{
	SocketServerTCP		socketServer;
	std::vector<int>	socketsClients;
	int					clientSocketID = INVALID_SOCKET;

	if (socketServer.init("127.0.0.1", 4242) == false
		|| socketServer.launch() == false)
	{
		OutputDebugString("INIT FAILED\n");
		return (1);
	}
	OutputDebugString("INIT OK\n");

	while (42)
	{
		if ((clientSocketID = socketServer.acceptNewClient()) != -1)
		{
			//_clientManager.addClient(clientSocketID);
			//socketsClients.push_back(clientSocketID);
			//socketServer.sendData();

			std::string msg = "hello\n";
			char buf[512];

			memset(buf, 0, 512);
			send(clientSocketID, msg.c_str(), msg.size(), 0);
			recv(clientSocketID, buf, 512, 0);
			OutputDebugString("---------->");
			OutputDebugString(buf);
			OutputDebugString("\n");
			closesocket(clientSocketID);
		}

	}
	return (0);
}
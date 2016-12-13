#include "client.hh"
#include "SocketClientTCP.hh"
#include "SocketClientUDP.hh"

int main()
{
	//ISocket *sock = new SocketClientTCP();
	//char	*rec = NULL;
	//std::string msg;

	//sock->init("127.0.0.1", 4242);
	//sock->connectToServer();
	//while (1)
	//{
	//	std::cin >> msg;
	//	sock->sendData(msg.c_str());
	//}
	//while ((rec = sock->receiveData()) == NULL);
	//std::cout << rec << std::endl;
	//sock->close();
	//while (35);


	//SocketClientUDP *sock = new SocketClientUDP();
	//char	*rec = NULL;
	//std::string msg;

	//sock->init("127.0.0.1", 4242);
	//sock->connectToServer();
	////while (1)
	////{
	////	std::cin >> msg;
	////	sock->sendData(msg.c_str());
	////}
	//while (1)
	//{
	//	while ((rec = sock->receiveData()) == NULL);
	//	std::cout << rec << std::endl;
	//}
	//sock->close();
	//while (35);

	Client client;

	client.launch();
	return (0);
}

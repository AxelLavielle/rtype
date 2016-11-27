#include "Client.hh"
#include "SocketClientTCP.hh"

int main()
{
	ISocket *sock = new SocketClientTCP();
	char	*rec = NULL;
	std::string msg;

	std::cout << "lol" << std::endl;
	sock->init("10.16.252.162", 4242);
	std::cout << "lol1" << std::endl;
	sock->connectToServer();
	std::cout << "lol2" << std::endl;
	while (1)
	{
		std::cin >> msg;
		sock->sendData(msg.c_str());
		//sock->sendData("wesh alors anthony bg du 06");
	}
	//while ((rec = sock->receiveData()) == NULL);
	//std::cout << rec << std::endl;
	while (35);
//	Client client;

//	client.launch();
}
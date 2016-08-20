#ifndef LISTENSERVER_H_
#define LISTENSERVER_H_

#pragma comment (lib, "Ws2_32.lib")

#define SERVERPORT htons(2050)

#include <WinSock2.h>

class ListenServer
{
public:
	ListenServer();
	~ListenServer();
	void start();
	void Stop();
private:
	void acceptClientsAsync();
	bool terminating;
	SOCKET skt;
};

#endif // !LISTENSERVER_H_

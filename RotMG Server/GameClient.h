#ifndef GAMECLIENT_H_
#define GAMECLIENT_H_

#include "ClientSock.h"
#include <WinSock2.h>

class Message;
class Player;

class GameClient
{
public:
	GameClient(SOCKET* targetSocket, sockaddr_in* info)
		: connection(targetSocket, info, this) { }
	~GameClient() {
		connection.~ClientSock();
	}
	void startHandling();
	void sendMessage(Message* message);
	void handleMessage(int messageId, Message* message);
	void disconnect(const char* reason, bool immediate);
	Player* player;
private:
	ClientSock connection;
};

#endif // !GAMECLIENT_H_

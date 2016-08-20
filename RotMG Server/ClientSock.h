#ifndef CLIENTSOCK_H_
#define CLIENTSOCK_H_

#include <WinSock2.h>
#include <ppltasks.h>
#include <queue>

typedef struct {
	const char* data;
	int length;
} MessageInfo;

class Message;
class GameClient;

class ClientSock
{
public:
	ClientSock(SOCKET* skt, sockaddr_in* info, GameClient* client);
	~ClientSock();
	void begin();
	void sendMessage(Message* message);
	void disconnect(bool immediate);
private:
	SOCKET* skt;
	sockaddr_in* info;
	GameClient* client;
	bool disconnected;
	bool disconnecting;
	std::atomic<bool> sending;
	std::queue<MessageInfo*>* pendingMessages;

	void disconnectInternal();
	void sendPendingMessages();

	int recvFull(char* dst, size_t len, int flags);
	int sendFull(char* data, size_t len, int flags);
};
#endif // !CLIENTSOCK_H_

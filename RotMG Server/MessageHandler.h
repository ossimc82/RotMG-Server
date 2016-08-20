#ifndef MESSAGEHANDLER_H_
#define MESSAGEHANDLER_H_

#define NO_MESSAGE_HANDLER NoMessageHandler

class Message;
class GameClient;

class MessageHandlerBase
{
public:
	MessageHandlerBase();
	~MessageHandlerBase();
	virtual void handle(GameClient* client, Message* message) = 0;
private:

};

inline MessageHandlerBase::MessageHandlerBase()
{
}

inline MessageHandlerBase::~MessageHandlerBase()
{
}

template<typename TMessage>
class MessageHandler : public MessageHandlerBase
{
public:
	MessageHandler() { }
	~MessageHandler() { }

	void handle(GameClient* client, Message* message);
protected:
	GameClient* client;
	virtual void handleMessage(TMessage* message) = 0;
};

template<typename TMessage>
inline void MessageHandler<TMessage>::handle(GameClient* client, Message* message) {
	this->client = client;
	handleMessage((TMessage*)message);
}

typedef struct NoMessageHandler : public MessageHandlerBase {
	inline void NoMessageHandler::handle(GameClient* client, Message* message) {
	}
};

/* ------------------------------------ Handler class declarations ------------------------------------ */

class HelloMessage;

class HelloMessageHandler : public MessageHandler<HelloMessage>
{
public:
	HelloMessageHandler(){}
	~HelloMessageHandler(){}

protected:
	void handleMessage(HelloMessage* message);
};

#endif // !MESSAGEHANDLER_H_

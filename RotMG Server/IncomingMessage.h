#ifndef INCOMMINGMESSAGE_H_
#define INCOMMINGMESSAGE_H_

#include "Message.h"
class MessageDataReader;

class IncomingMessage : public Message
{
public:
	IncomingMessage(){}
	~IncomingMessage(){}
	virtual void readFromInput(MessageDataReader* rdr) = 0;
};



/* ------------------------------- Incoming Messages ------------------------------- */

class HelloMessage : public IncomingMessage
{
public:
	HelloMessage(){}
	~HelloMessage(){}
	void readFromInput(MessageDataReader* rdr);
	unsigned char getMessageId() {
		return HELLO;
	}

	char*			buildVersion;
	int				gameId;
	char*			guid;
	char*			password;
	char*			secret;
	int				keyTime;
	unsigned char*	key;
	unsigned char*	mapJson;
	char*			entryTag;
	char*			gameNet;
	char*			gameNetUserId;
	char*			playPlatform;
	char*			platformToken;
	char*			client;
};

class CreateMessage : public IncomingMessage
{
public:
	CreateMessage(){};
	~CreateMessage(){};
	void readFromInput(MessageDataReader* rdr);
	unsigned char getMessageId() {
		return CREATE;
	}

	int classType;
	int skinType;
};

#endif // !INCOMMINGMESSAGE_H_

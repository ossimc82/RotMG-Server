#ifndef OUTGOINGMESSAGE_H_
#define OUTGOINGMESSAGE_H_

#include <string>
#include <vector>
#include "Message.h"

class MessageDataWriter;

class OutgoingMessage : public Message
{
public:
	OutgoingMessage(){}
	~OutgoingMessage(){}

	virtual void writeToOutput(MessageDataWriter* wtr) = 0;
};


/* ------------------------------- Outgoing Messages ------------------------------- */

class FailureMessage : public OutgoingMessage {
public:
	FailureMessage(){}
	~FailureMessage(){}

	int			errorId;
	const char* errorMessage;
	void writeToOutput(MessageDataWriter* wtr);
	unsigned char getMessageId() {
		return FAILURE;
	}
};

class MapInfoMessage : public OutgoingMessage {
public:
	MapInfoMessage() {}
	~MapInfoMessage() {}

	int							width;
	int							height;
	const char*					name;
	const char*					displayName;
	int							difficulty;
	unsigned int				fp;
	int							background;
	bool						allowPlayerTeleport;
	bool						showDisplays;
	std::vector<std::string>	clientXML;
	std::vector<std::string>	extraXML;

	void writeToOutput(MessageDataWriter* wtr);
	unsigned char getMessageId() {
		return MAPINFO;
	}
};

#endif // !OUTGOINGMESSAGE_H_
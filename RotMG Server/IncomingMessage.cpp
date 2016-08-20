#include "IncomingMessage.h"
#include "MessageDataReader.h"

void HelloMessage::readFromInput(MessageDataReader* rdr) {
	buildVersion = rdr->readUTF();
	gameId = rdr->readInt32();
	guid = rdr->readUTF();
	password = rdr->readUTF();
	secret = rdr->readUTF();
	keyTime = rdr->readInt32();

	short keyLen = rdr->readInt16()+1;
	key = new unsigned char[keyLen];
	rdr->read(key, keyLen-1);
	NULLTERMINATESTRING(key, keyLen);

	int mapJsonLength = rdr->readInt32()+1;
	mapJson = new unsigned char[mapJsonLength];
	rdr->read(mapJson, mapJsonLength-1);
	NULLTERMINATESTRING(mapJson, mapJsonLength);

	entryTag = rdr->readUTF();
	gameNet = rdr->readUTF();
	gameNetUserId = rdr->readUTF();
	playPlatform = rdr->readUTF();
	platformToken = rdr->readUTF();
	if (rdr->bytesAvailable(2)) {
		client = rdr->readUTF();
	}
}

void CreateMessage::readFromInput(MessageDataReader* rdr) {
	classType = rdr->readInt16();
	skinType = rdr->readInt16();
}

#include "MessageDataWriter.h"
#include <WinSock2.h>

MessageDataWriter::MessageDataWriter(char messageId) {
	this->messageId = messageId;
}

MessageDataWriter::~MessageDataWriter() {
}

void MessageDataWriter::writeBoolean(const bool value) {
	writeSocketData((char*)&value, sizeof(bool));
}

void MessageDataWriter::writeInt8(const char value) {
	writeSocketData((char*)&value, sizeof(char));
}

void MessageDataWriter::writeInt16(const short value) {
	int16_t val = htons(value);
	writeSocketData((char*)&val, sizeof(int16_t));
}

void MessageDataWriter::writeInt32(const int value) {
	int32_t val = htonl(value);
	writeSocketData((char*)&val, sizeof(int32_t));
}

void MessageDataWriter::writeUTF(const char* value) {
	int16_t strLen = strlen(value);
	writeInt16(strLen);
	writeSocketData((char*)value, strLen);
}

void MessageDataWriter::writeUInt8(const unsigned char value) {
	writeSocketData((char*)&value, sizeof(unsigned char));
}

void MessageDataWriter::writeUInt16(const unsigned short value) {
	uint16_t val = htons(value);
	writeSocketData((char*)&val, sizeof(uint16_t));
}

void MessageDataWriter::writeUInt32(const unsigned int value) {
	uint32_t val = htonl(value);
	writeSocketData((char*)&val, sizeof(uint32_t));
}

void MessageDataWriter::writeUTF32(const char* value) {
	int32_t strLen = strlen(value);
	writeInt32(strLen);
	writeSocketData((char*)value, strLen);
}

void MessageDataWriter::writeSocketData(char* data, int dataLength) {
	const int32_t newLen = length + dataLength;
	char* newStreamData = new char[newLen];

	memcpy(newStreamData, streamData, length);
	memcpy(newStreamData + length, data, dataLength);

	delete streamData;
	streamData = newStreamData;
	length = newLen;
}

char* MessageDataWriter::getFinalData() {
	const int32_t finalDataLength = length + 5;
	char* finalData = new char[finalDataLength];

	int networkLen = htonl(finalDataLength);

	memcpy(finalData, &networkLen, 4);
	memcpy(finalData + 4, &messageId, 1);
	memcpy(finalData + 5, streamData, length);

	delete streamData;
	return finalData;
}

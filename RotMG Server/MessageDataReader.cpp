#include "MessageDataReader.h"
#include <WinSock2.h>
#include <iostream>

signed char MessageDataReader::readInt8() {
	int8_t value;
	read(&value, sizeof(int8_t));
	return value;
}

int16_t MessageDataReader::readInt16() {
	int16_t value;
	read(&value, sizeof(int16_t));
	value = ntohs(value);
	return value;
}

int32_t MessageDataReader::readInt32() {
	int32_t value;
	read(&value, sizeof(int32_t));
	value = ntohl(value);
	return value;
}

int64_t MessageDataReader::readInt64() {
	int64_t value;
	read(&value, sizeof(int64_t));
	value = ntohl(value);
	return value;
}

char* MessageDataReader::readUTF() {
	int16_t len = readInt16()+1;
	char* dst = new char[len];
	read(dst, len-1);
	dst[len-1] = '\0'; //Null terminate string to avoid reading over the string
	return dst;
}

void MessageDataReader::read(void* dest, size_t length) {
	if (length == 0) {
		return;
	}

	//check length to avoid overflow
	if (pos + length > buffLen) {
		throw std::runtime_error("Cannot read beyond the buffer");
	}

	memcpy(dest, streamData + pos, length);
	pos += length;
}

bool MessageDataReader::bytesAvailable(int minCount) {
	int available = (buffLen - pos);
	return available >= minCount;
}

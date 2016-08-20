#ifndef MESSAGEDATAWRITER_H_
#define MESSAGEDATAWRITER_H_

#include <stdint.h>

class MessageDataWriter {
public:
	MessageDataWriter(char messageId);
	~MessageDataWriter();
	char* getFinalData();

	void writeBoolean(const bool value);

	void writeInt8(const char value);
	void writeInt16(const short value);
	void writeInt32(const int value);
	void writeUTF(const char* value);

	void writeUInt8(const unsigned char value);
	void writeUInt16(const unsigned short value);
	void writeUInt32(const unsigned int value);
	void writeUTF32(const char* value);
	int32_t length;
private:
	void writeSocketData(char* data, int dataLength);
	char messageId;
	char* streamData;
};

#endif // !MESSAGEDATAWRITER_H_
#ifndef MESSAGEDATAREADER_H_
#define MESSAGEDATAREADER_H_

#include <stdint.h>

class MessageDataReader
{
public:
	MessageDataReader(const char* buff, int buffLen) {
		streamData = buff;
		this->buffLen = buffLen;
	}
	~MessageDataReader() {
		delete streamData;
	}

	signed char	readInt8();
	int16_t		readInt16();
	int32_t		readInt32();
	int64_t		readInt64();
	char*		readUTF();

	void read(void* dest, size_t length);
	bool bytesAvailable(int minCount = 1);
private:
	const char* streamData;
	int pos = 0;
	int buffLen;
};

#endif // !MESSAGEDATAREADER_H_
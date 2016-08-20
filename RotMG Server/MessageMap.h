#ifndef MESSAGEMAP_H_
#define MESSAGEMAP_H_

#include <unordered_map>

class Message;
struct MessageCreatorBase;
struct MessageHandlerBase;

class MessageMap
{
public:
	static Message* NewMessage(int messageId);
	static MessageHandlerBase* NewHandler(int messageId);
private:
	static void createMappingIfRequired();
	static std::unordered_map<int, MessageCreatorBase*>* messageIdMap;
};

#endif // !MESSAGEMAP_H_

#include "MessageMap.h"
#include "MessageHandler.h"
#include "OutgoingMessage.h"
#include "IncomingMessage.h"

struct MessageCreatorBase {
	virtual Message* createMessage() = 0;
	virtual MessageHandlerBase* createHandler() = 0;
};

template<typename TMessage, typename TMessageHandler>
struct MessageCreator : public MessageCreatorBase
{
	virtual Message* createMessage() {
		return new TMessage();
	}

	virtual MessageHandlerBase* createHandler() {
		return new TMessageHandler();
	}
};

std::unordered_map<int, MessageCreatorBase*>* MessageMap::messageIdMap;

MessageHandlerBase* MessageMap::NewHandler(int messageId)
{
	createMappingIfRequired();
	return messageIdMap->at(messageId)->createHandler();
}

Message* MessageMap::NewMessage(int messageId)
{
	createMappingIfRequired();
	return messageIdMap->at(messageId)->createMessage();
}

void MessageMap::createMappingIfRequired() {
	if (messageIdMap == NULL) {
		messageIdMap = new std::unordered_map<int, MessageCreatorBase*>();
		messageIdMap->insert(std::make_pair(FAILURE, new MessageCreator<FailureMessage, NO_MESSAGE_HANDLER>()));
		messageIdMap->insert(std::make_pair(MAPINFO, new MessageCreator<MapInfoMessage, NO_MESSAGE_HANDLER>()));
		messageIdMap->insert(std::make_pair(HELLO, new MessageCreator<HelloMessage, HelloMessageHandler>()));
	}
}
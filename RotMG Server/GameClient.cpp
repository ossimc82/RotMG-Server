#include "GameClient.h"
#include "MessageMap.h"
#include "MessageHandler.h"
#include "Message.h"
#include "ClientSock.h"
#include <iostream>

void GameClient::startHandling() {
	connection.begin();
}

void GameClient::sendMessage(Message* message) {
	connection.sendMessage(message);
}

void GameClient::handleMessage(int messageId, Message* message) {
	MessageHandlerBase* handler = MessageMap::NewHandler(messageId);
	handler->handle(this, message);
}

void GameClient::disconnect(const char* reason, bool immediate) {
	std::cout << "Requesting disconnect for client " << this << " Reason: " << reason << std::endl;
	connection.disconnect(immediate);
}
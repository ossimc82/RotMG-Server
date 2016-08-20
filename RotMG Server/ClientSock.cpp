#include "ClientSock.h"
#include "GameClient.h"
#include "MessageDataReader.h"
#include "MessageMap.h"
#include "MessageDataWriter.h"
#include "OutgoingMessage.h"
#include "IncomingMessage.h"
#include <iostream>
#include <WinSock2.h>

ClientSock::ClientSock(SOCKET* skt, sockaddr_in* info, GameClient* client) {
	this->skt = skt;
	this->info = info;
	this->client = client;
	pendingMessages = new std::queue<MessageInfo*>();
}

ClientSock::~ClientSock() {
}

void ClientSock::begin() {
	concurrency::task<void>t([this]() {
		while (true) {
			int messageLength;
			int receiveCode = recvFull((char*)&messageLength, sizeof(int32_t), 0);
			if (receiveCode != 0) {
				if (receiveCode != INT32_MIN) {
					std::cout << "socket read error " << receiveCode << std::endl;
				}
				disconnectInternal();
				return;
			}

			messageLength = ntohl(messageLength);

			char messageId;
			receiveCode = recvFull(&messageId, sizeof(char), 0);
			if (receiveCode != 0) {
				if (receiveCode != INT32_MIN) {
					std::cout << "socket read error " << receiveCode << std::endl;
				}
				disconnectInternal();
				return;
			}

			if (*(((char*)&messageLength) + 0) == 0x4d &&
				*(((char*)&messageLength) + 1) == 0x61 &&
				*(((char*)&messageLength) + 2) == 0x64 &&
				*(((char*)&messageLength) + 3) == 0x65 &&
				messageId == 0xff) {
				const char* crossdomain =
					"<cross-domain-policy><site-control permitted-cross-domain-policies=\"master-only\"/><allow-access-from domain=\"*\" secure=\"false\"/><allow-http-request-headers-from domain=\"*\" headers=\"*\" secure=\"false\"/></cross-domain-policy>\r\n";
				int sendCode = sendFull((char*)crossdomain, strlen(crossdomain), 0);
				if (sendCode != 0) {
					if (sendCode != INT32_MIN) {
						std::cout << "socket send error " << sendCode << std::endl;
					}
				}
				disconnectInternal();
			}

			int messageDataLength = messageLength - 5;
			char* messageData = new char[messageDataLength];
			receiveCode = recvFull(messageData, messageDataLength, 0);
			if (receiveCode != 0) {
				if (receiveCode != INT32_MIN) {
					std::cout << "socket read error " << receiveCode << std::endl;
				}
				disconnectInternal();
				return;
			}

			Message* msg = MessageMap::NewMessage(messageId);
			((IncomingMessage*)msg)->readFromInput(&MessageDataReader(messageData, messageDataLength));
			client->handleMessage(messageId, msg);
		}
	});
}

void ClientSock::sendMessage(Message* message) {
	if (disconnecting) {
		return;
	}
	MessageInfo* info = new MessageInfo();
	
	OutgoingMessage* outgoing = (OutgoingMessage*)message;
	if (outgoing != NULL) {
		MessageDataWriter wtr(message->getMessageId());
		outgoing->writeToOutput(&wtr);
		info->data = wtr.getFinalData();
		info->length = wtr.length + 5;
	}

	pendingMessages->push(info);
	sendPendingMessages();
}

void ClientSock::disconnect(bool immediate) {
	disconnecting = true;

	if (immediate || (pendingMessages->size() == 0 && !sending)) {
		disconnectInternal();
		return;
	}
}

void ClientSock::disconnectInternal() {
	disconnected = true;
	closesocket(*skt);
	shutdown(*skt, 0);
}

void ClientSock::sendPendingMessages() {
	concurrency::task<void> t([this]() {
		if (sending) {
			return;
		}
		if (pendingMessages->size() == 0) {
			if (disconnecting) {
				disconnect(disconnecting);
			}
			return;
		}

		sending = true;
		MessageInfo* first = pendingMessages->front();
		pendingMessages->pop();
		int sendCode = sendFull((char*)first->data, first->length, 0);
		if (sendCode != 0) {
			if (sendCode != INT32_MIN) {
				std::cout << "socket send error " << sendCode << std::endl;
			}
			disconnectInternal();
			return;
		}
		sending = false;
		sendPendingMessages();
	});
}
int ClientSock::recvFull(char* dst, size_t len, int flags) {
	int left = len;
	while (left > 0) {
		int result = recv(*skt, dst + (len - left), left, flags);
		if (result == 0) {
			//Socket disconnected
			return INT32_MIN;
		}
		if (result == SOCKET_ERROR) {
			return WSAGetLastError();
		}
		left -= result;
	}
	return 0;
}

int ClientSock::sendFull(char* data, size_t len, int flags) {
	int left = len;
	while (left > 0) {
		int result = send(*skt, data + (len - left), left, flags);
		if (result == 0) {
			//Socket disconnected
			return INT32_MIN;
		}
		if (result == -1) {
			return WSAGetLastError();
		}
		left -= result;
	}
	return 0;
}
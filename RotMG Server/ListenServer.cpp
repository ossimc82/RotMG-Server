#include "ListenServer.h"
#include <iostream>
#include <ppltasks.h>
#include "GameClient.h"

ListenServer::ListenServer() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	skt = socket(AF_INET, SOCK_STREAM, 0);
	if (skt == INVALID_SOCKET) {
		WSACleanup();
		int result = WSAGetLastError();
		throw result;
	}
}

void ListenServer::start() {
	sockaddr_in in = sockaddr_in();
	in.sin_family = AF_INET;
	in.sin_port = SERVERPORT;

	int result = bind(skt, (sockaddr*)&in, sizeof(sockaddr));
	if (result != 0) {
		result = WSAGetLastError();
		throw result;
	}

	result = listen(skt, 0);
	if (result != 0) {
		result = WSAGetLastError();
		throw result;
	}
	std::cout << "Listening on " << SERVERPORT << std::endl;
	acceptClientsAsync();
}

void ListenServer::Stop() {
	terminating = true;
}

void ListenServer::acceptClientsAsync() {
	concurrency::task<void> t([this]() {
		while (true) {
			int len = sizeof(sockaddr_in);
			struct sockaddr_in info;
			SOCKET clientSocket = accept(skt, (struct sockaddr*)&info, &len);
			std::cout << "Client accepted " << info.sin_addr.S_un.S_addr << std::endl;

			GameClient gClient(&clientSocket, &info);
			gClient.startHandling();
		}
	});
}

ListenServer::~ListenServer() {
	closesocket(skt);
	WSACleanup();
	//delete &skt;
}
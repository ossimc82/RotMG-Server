// RotMG Server.cpp : Defines the entry point for the console application.
//

#include "ListenServer.h"
#include "RealmManager.h"
#include "GameObject.h"
#include <iostream>

int main() {
	RealmManager manager;
	manager.start();

	ListenServer server;
	server.start();

	while (true);
	
	return 0;
}

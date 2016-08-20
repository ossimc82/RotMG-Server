#include "LogicLoop.h"
#include <Windows.h>
#include <iostream>
#include "World.h"
#include "RealmManager.h"

void LogicLoop::start() {
	logicThread = new std::thread(&LogicLoop::loop, this);
}

void LogicLoop::loop() {
	double start = GetTickCount();
	double currentTime = 0;
	double elapsedSinceLastUpdate = 0;

	while (true) {
		double t = GetTickCount() - start;
		elapsedSinceLastUpdate = t - currentTime;
		currentTime = t;
		update(currentTime / 1000, elapsedSinceLastUpdate / 1000);
		double timeToUpdate = GetTickCount() - start - currentTime;
		if (timeToUpdate < 200)
			Sleep(200 - timeToUpdate);
	}
}

void LogicLoop::update(double time, double dt) {
	std::cout << "current time: " << time << "   delta: " << dt << std::endl;
	for each (std::pair<int, World*> worldPair in *manager->worlds) {
		worldPair.second->update(time, dt);
	}
}

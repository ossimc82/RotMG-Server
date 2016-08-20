#include "RealmManager.h"
#include "LogicLoop.h"
#include "Game.h"
#include "World.h"
#include "Player.h"
#include "OutgoingMessage.h"

RealmManager* RealmManager::instance;

RealmManager::RealmManager() {
	if (instance != NULL) {
		throw std::runtime_error("RealmManager already initialized");
	}

	worlds = new unordered_map<int, World*>();
	instance = this;
}

RealmManager::~RealmManager() {
}

void RealmManager::start() {
	Game::LoadXmls();
	logicLoop = new LogicLoop(this);

	worlds->insert(make_pair(-2, new World("Nexus")));
}

/* static */
MapInfoMessage* RealmManager::RegisterPlayerInWorld(int gameId, Player* player) {
	if (instance->worlds->find(gameId) == instance->worlds->end()) {
		return NULL;
	}

	World* world = instance->worlds->at(gameId);
	if (world->isLimbo) {
		world = new World(*world);
	}
	player->setGame(world);
	return world->mapInfo();
}

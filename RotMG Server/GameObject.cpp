#include "GameObject.h"
#include "Stat.h"
#include "Game.h"
#include <unordered_map>

using std::make_pair;

GameObject::GameObject() {
	stats = new std::unordered_map<int, Stat*>();
	updatedStats = new std::unordered_set<int>();
}

GameObject::~GameObject() {
}

std::string GameObject::name() {
	Stat* stat = getObjectStat(NAME_STAT);
	return stat->stringValue;
}

void GameObject::setName(std::string name) {
	if (this->name() == name) {
		return;
	}

	updatedStats->insert(NAME_STAT);
	Stat* stat = getObjectStat(NAME_STAT);
	stat->stringValue = name;
}


std::string GameObject::idName() {
	return Game::ObjectIdFromType(type);
}

void GameObject::setGame(World* game) {
	if (m_game != NULL) {
		throw std::runtime_error("Game already set");
	}
	m_game = game;
}

Stat* GameObject::getObjectStat(unsigned int type) {
	if (stats->find(type) == stats->end()) {
		Stat* stat = new Stat();
		stat->statType = type;
		stats->insert(make_pair(type, stat));
	}
	return stats->at(type);
}

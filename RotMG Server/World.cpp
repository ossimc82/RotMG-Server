#include "World.h"
#include "GameObject.h"
#include "OutgoingMessage.h"
#include "Game.h"
#include "XMLWorld.h"
#include "XMLRoom.h"
#include "Random.h"
#include "ParsedMap.h"

World::World(const char* xmlId) {
	xmlWorld = Game::WorldFromId(xmlId);
	width = xmlWorld->width;
	height = xmlWorld->height;
	name = xmlWorld->id.c_str();
	displayName = xmlWorld->id.c_str();
	difficulty = xmlWorld->difficulty;
	fp = Random::randomSeed();
	background = xmlWorld->background;
	allowPlayerTeleport = xmlWorld->allowPlayerTeleport;
	showDisplays = xmlWorld->showDisplays;

	buildMap();
}

World::~World() {
}

void World::buildMap() {

	tiles = new std::vector<Tile*>();

	Tile defaultTile;
	defaultTile.tileType = xmlWorld->defaultTile;

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < width; y++) {
			defaultTile.x = x;
			defaultTile.y = y;
			tiles->push_back(new Tile(defaultTile));
		}
	}

	XMLRoom* start = xmlWorld->getRoom("start");
	if (start == NULL) {
		//TODO: remove world
		return;
	}
	start->getRandomJM()->addToMapCenter(this, width/2, height/2);
}

void World::setTile(int x, int y, Tile tile) {
	tiles->at(x + y * width) = new Tile(tile);
}

void World::update(double time, double dt) {
}

MapInfoMessage* World::mapInfo() {
	MapInfoMessage* info = new MapInfoMessage();
	info->width = width;
	info->height = height;
	info->name = name;
	info->displayName = displayName;
	info->difficulty = difficulty;
	info->fp = fp;
	info->background = background;
	info->allowPlayerTeleport = allowPlayerTeleport;
	info->showDisplays = showDisplays;
	return info;
}

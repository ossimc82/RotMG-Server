#include "XMLWorld.h"
#include "XMLRoom.h"
#include "Util.h"
#include "Game.h"

XMLWorld::XMLWorld(xml_node worldNode) {
	rooms = new std::unordered_map<std::string, std::vector<XMLRoom*>*>();
	id = worldNode.attribute("id").as_string();
	width = worldNode.select_node("Width").node().text().as_int();
	height = worldNode.select_node("Height").node().text().as_int();
	background = worldNode.select_node("Background").node().text().as_int();
	difficulty = worldNode.select_node("Difficulty").node().text().as_int();
	defaultTile = Game::GroundTypeFromId(worldNode.select_node("DefaultTile").node().text().as_string());
	centerStartRoom = XNODE_EXISTS(worldNode.select_node("CenterStartRoom"));
	visibility = worldNode.select_node("Visibility").node().text().as_string();
	showDisplays = XNODE_EXISTS(worldNode.select_node("ShowDisplays"));
	allowPlayerTeleport = !XNODE_EXISTS(worldNode.select_node("NoPlayerTeleport"));

	for each (xpath_node xRoomNode in worldNode.select_nodes("Room")) {
		xml_node roomNode = xRoomNode.node();

		std::string type = roomNode.attribute("id").as_string();

		if (rooms->find(type) == rooms->end()) {
			rooms->insert(make_pair(type, new std::vector<XMLRoom*>()));
		}
		rooms->at(type)->push_back(new XMLRoom(roomNode));		
	}
}

XMLRoom* XMLWorld::getRoom(const char* type) {
	if (rooms->find(type) == rooms->end()) {
		return NULL;
	}

	std::vector<XMLRoom*>* candidates = rooms->at(type);
	if (candidates == NULL) {
		return NULL;
	}

	return candidates->at(Util::randomRange(0, candidates->size() - 1));
}

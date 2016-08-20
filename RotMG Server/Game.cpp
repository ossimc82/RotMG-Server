#include "Game.h"
#include "xml.h"
#include "XMLItem.h"
#include "XMLEnemy.h"
#include "XMLWorld.h"
#include <iostream>

unordered_map<string, int>* Game::idToType;
unordered_map<string, vector<XMLEnemy*>*>* Game::enemyGroups;
unordered_map<int, XMLEnemy*>* Game::enemies;
unordered_map<int, xml_node*>* Game::xmlLibrary;
unordered_map<int, XMLItem*>* Game::items;
unordered_map<string, int>* Game::groundIdToType;
unordered_map<string, XMLWorld*>* Game::idToWorld;

void Game::LoadXmls() {
	if (idToType != NULL) {
		throw std::runtime_error("xmls already loaded");
	}
	idToType = new unordered_map<string, int>();
	enemyGroups = new unordered_map<string, vector<XMLEnemy*>*>();
	enemies = new unordered_map<int, XMLEnemy*>();
	xmlLibrary = new unordered_map<int, xml_node*>();
	items = new unordered_map<int, XMLItem*>();
	groundIdToType = new unordered_map<string, int>();
	idToWorld = new unordered_map<string, XMLWorld*>();

	loadXml("equip.xml");
	loadXml("nexus.xml");
	//TODO: add the others
}

void Game::loadXml(const char* fileName) {
	XML curr(fileName);
	std::cout << "Loading xml... " << fileName << std::endl;
	if (!curr.success) {
		std::cout << "Error loading xml (" << fileName << ") [" << curr.loadMessage << "]" << std::endl;
		return;
	}

	loadObjects(&curr);
	loadGrounds(&curr);
	loadDungeons(&curr);	
}

void Game::loadObjects(XML* curr) {
	for each (xpath_node xnode in curr->doc.select_node("Objects").node().select_nodes("Object")) {
		xml_node node = xnode.node();
		if (node == NULL) {
			continue;
		}
		const char* id = node.attribute("id").as_string();
		int type = node.attribute("type").as_int();
		const char* objClass = node.select_node("Class").node().text().as_string();
		bool isEnemy = XNODE_EXISTS(node.select_node("Enemy"));
		bool isPlayer = XNODE_EXISTS(node.select_node("Player"));
		bool isItem = XNODE_EXISTS(node.select_node("Item"));

		xmlLibrary->insert(make_pair(type, &node));
		idToType->insert(make_pair(id, type));

		if (isItem) {
			items->insert(make_pair(type, new XMLItem(node)));
		}
		if (isEnemy) {
			const char* group = node.select_node("Group").node().text().as_string();
			if (enemyGroups->find(group) == enemyGroups->end()) {
				enemyGroups->insert(make_pair(group, new vector<XMLEnemy*>()));
			}
			XMLEnemy* enemy = new XMLEnemy(node);
			enemyGroups->find(group)->second->push_back(enemy);
			enemies->insert(make_pair(type, enemy));
		}
	}
}

void Game::loadGrounds(XML* curr) {
	for each (xpath_node xnode in curr->doc.select_node("Grounds").node().select_nodes("Ground")) {
		xml_node node = xnode.node();
	}
}

void Game::loadDungeons(XML* curr) {
	for each (xpath_node xnode in curr->doc.select_node("Dungeons").node().select_nodes("Dungeon")) {
		xml_node node = xnode.node();
		XMLWorld* w = new XMLWorld(node);

		idToWorld->insert(make_pair(w->id, w));
	}
}

std::string Game::ObjectIdFromType(const int type) {
	if (xmlLibrary->find(type) == xmlLibrary->end()) {
		return "";
	}
	return xmlLibrary->at(type)->attribute("id").as_string();
}

std::string Game::DisplayIdFromType(const int type) {
	if (xmlLibrary->find(type) == xmlLibrary->end()) {
		return "";
	}
	xml_node* objXml = xmlLibrary->at(type);
	xpath_node xDisplayIdNode = objXml->select_node("DisplayId");
	if (XNODE_EXISTS(xDisplayIdNode))
		return xDisplayIdNode.node().text().as_string();
	return objXml->attribute("id").as_string();
}

int Game::ObjectTypeFromId(const char* id) {
	if (idToType->find(id) == idToType->end()) {
		return -1;
	}
	return idToType->at(id);
}

vector<int> Game::EnemyTypesFromGroup(const char* group) {
	vector<int> types;
	if (enemyGroups->find(group) == enemyGroups->end()) {
		return types;
	}

	vector<XMLEnemy*>* enemies = enemyGroups->at(group);

	for each (XMLEnemy* enemy in *enemies) {
		types.push_back(enemy->type);
	}
	return types;
}

int Game::GroundTypeFromId(const char* id) {
	if (groundIdToType->find(id) == groundIdToType->end()) {
		return -1;
	}
	return idToType->at(id);
}

XMLWorld* Game::WorldFromId(const char* id) {
	if (idToWorld->find(id) == idToWorld->end()) {
		return NULL;
	}
	return idToWorld->at(id);
}

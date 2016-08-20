#ifndef XMLWORLD_H_
#define XMLWORLD_H_

#include <string>
#include <unordered_map>
#include "pugixml.hpp"

using std::string;
using pugi::xml_node;
using pugi::xpath_node;
using pugi::xml_attribute;
using pugi::xml_node_type;

class XMLRoom;

class XMLWorld {
public:
	XMLWorld(xml_node worldNode);

	std::string id;
	int width;
	int height;
	int background;
	int difficulty;
	std::string visibility;
	bool showDisplays;
	bool allowPlayerTeleport;
	bool centerStartRoom;
	int defaultTile;

	std::unordered_map<std::string, std::vector<XMLRoom*>*>* rooms;

	XMLRoom* getRoom(const char* type);
private:

};

#endif // !XMLWORLD_H_

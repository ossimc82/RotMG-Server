#include "XMLRoom.h"
#include "ParsedMap.h"
#include "Util.h"

XMLRoom::XMLRoom(xml_node roomNode) {
	type = roomNode.attribute("id").as_string();

	localjms = new std::vector<std::string>();

	for each (xpath_node xnode in roomNode.select_nodes("LocalJM")) {
		localjms->push_back(xnode.node().text().as_string());
	}
}

ParsedMap* XMLRoom::getRandomJM() {
	return ParsedMap::ParseFromFile(localjms->at(Util::randomRange(0, localjms->size()-1)).c_str());
}

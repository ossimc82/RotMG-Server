#ifndef XMLROOM_H_
#define XMLROOM_H_

#include <string>
#include <unordered_map>
#include "pugixml.hpp"

using std::string;
using pugi::xml_node;
using pugi::xpath_node;
using pugi::xml_attribute;
using pugi::xml_node_type;

class ParsedMap;

class XMLRoom {
public:
	XMLRoom(xml_node roomNode);
	~XMLRoom() { }

	std::string type;
	std::vector<std::string>* localjms;

	ParsedMap* getRandomJM();
private:

};

#endif // !XMLROOM_H_

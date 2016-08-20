#ifndef XMLENEMY_H_
#define XMLENEMY_H_

#include <string>
#include <unordered_map>
#include "pugixml.hpp"

using std::string;
using pugi::xml_node;
using pugi::xpath_node;
using pugi::xml_attribute;
using pugi::xml_node_type;

class XMLEnemy {
public:
	XMLEnemy(xml_node enemyNode);
	~XMLEnemy() { }

	int type;
private:

};

#endif // !XMLENEMY_H_

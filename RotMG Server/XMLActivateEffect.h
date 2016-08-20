#ifndef XMLACTIVATEEFFECT_H_
#define XMLACTIVATEEFFECT_H_

//#include <string>
//#include <unordered_map>
#include "pugixml.hpp"

//using std::string;
using pugi::xml_node;
using pugi::xpath_node;
using pugi::xml_attribute;
using pugi::xml_node_type;

class XMLActivateEffect
{
public:
	XMLActivateEffect(xml_node activateNode);
	~XMLActivateEffect() { }

private:

};

#endif // !XMLACTIVATEEFFECT_H_

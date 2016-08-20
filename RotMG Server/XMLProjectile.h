#ifndef XMLPROJECTILE_H_
#define XMLPROJECTILE_H_

#include <string>
#include <vector>
#include "pugixml.hpp"

using std::string;
using pugi::xml_node;
using pugi::xpath_node;
using pugi::xml_attribute;
using pugi::xml_node_type;

class XMLConditionEffect;

class XMLProjectile
{
public:
	XMLProjectile(xml_node projectileNode);
	~XMLProjectile() { }

	int id;
	string objectId;
	int lifetimeMS;
	float speed;
	int size;
	int minDamage;
	int maxDamage;

	std::vector<XMLConditionEffect*>* effects;

	bool multiHit;
	bool passesCover;
	bool armorPiercing;
	bool particleTrail;
	bool wavy;
	bool parametric;
	bool boomerang;

	float amplitude;
	float frequency;
	float magnitude;
private:

};

#endif // !XMLPROJECTILE_H_

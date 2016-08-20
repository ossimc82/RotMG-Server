#ifndef ITEM_H_
#define ITEM_H_

#include <string>
#include <unordered_map>
#include "pugixml.hpp"

using std::string;
using pugi::xml_node;
using pugi::xpath_node;
using pugi::xml_attribute;
using pugi::xml_node_type;

class XMLProjectile;
class XMLActivateEffect;

class XMLItem
{
public:
	XMLItem(xml_node objectNode);
	~XMLItem() { }

	int objectType;
	string objectId;
	string objectClass;
	string displayId;
	int slotType;
	int tier;
	string description;
	float rateOfFire;
	bool usable;
	int bagType;
	int mpCost;
	int fameBonus;
	int numProjectiles;
	float arcGap;
	bool consumable;
	bool potion;
	string successorId;
	bool soulbound;
	float cooldown;
	bool resurrects;
	unsigned int texture1;
	unsigned int texture2;
	bool isBackpack;
	int doses;
	float ScaleValue;
	std::vector<std::pair<int, int>>* statsBoosts;
	std::vector<XMLActivateEffect*>* activateEffects;
	std::unordered_map<int, XMLProjectile*>* projectiles;
	int mpEndCost;
	float timer;
	bool xpBooster;
	bool lootDropBooster;
	bool lootTierBooster;
	
private:

};

#endif // !ITEM_H_

#include "XMLItem.h"
#include "XMLActivateEffect.h"
#include "XMLProjectile.h"

XMLItem::XMLItem(xml_node objectNode) {
	objectType = objectNode.attribute("type").as_int();
	objectId = objectNode.attribute("id").as_string();
	objectClass = objectNode.select_node("Class").node().text().as_string();
	displayId = objectNode.select_node("DisplayId").node().text().as_string(objectId.c_str());
	slotType = objectNode.select_node("SlotType").node().text().as_int();
	tier = objectNode.select_node("Tier").node().text().as_int(-1);
	description = objectNode.select_node("Description").node().text().as_string();
	rateOfFire = objectNode.select_node("RateOfFire").node().text().as_float();
	usable = XNODE_EXISTS(objectNode.select_node("Usable"));
	bagType = objectNode.select_node("BagType").node().text().as_int();
	mpCost = objectNode.select_node("MpCost").node().text().as_int();
	fameBonus = objectNode.select_node("FameBonus").node().text().as_int();
	numProjectiles = objectNode.select_node("NumProjectiles").node().text().as_int();
	arcGap = objectNode.select_node("ArcGap").node().text().as_float();
	consumable = XNODE_EXISTS(objectNode.select_node("Consumable"));
	potion = XNODE_EXISTS(objectNode.select_node("Potion"));
	successorId = objectNode.select_node("SuccessorId").node().text().as_string();
	soulbound = XNODE_EXISTS(objectNode.select_node("Soulbound"));
	cooldown = objectNode.select_node("Cooldown").node().text().as_int();
	resurrects = XNODE_EXISTS(objectNode.select_node("Resurrects"));
	texture1 = objectNode.select_node("Texture1").node().text().as_uint();
	texture2 = objectNode.select_node("Texture2").node().text().as_uint();
	isBackpack = XNODE_EXISTS(objectNode.select_node("IsBackpack"));
	doses = objectNode.select_node("Doses").node().text().as_int();
	mpEndCost = objectNode.select_node("MpEndCost").node().text().as_int();
	timer = objectNode.select_node("Timer").node().text().as_float();
	xpBooster = XNODE_EXISTS(objectNode.select_node("XpBoost"));
	lootDropBooster = XNODE_EXISTS(objectNode.select_node("LDBoosted"));
	lootTierBooster = XNODE_EXISTS(objectNode.select_node("LTBoosted"));

	statsBoosts = new std::vector<std::pair<int, int>>();
	for each (xpath_node xnode in objectNode.select_nodes("ActivateOnEquip")) {
		statsBoosts->push_back(std::make_pair(xnode.node().attribute("stat").as_int(),
			xnode.node().attribute("amount").as_int()));
	}

	activateEffects = new std::vector<XMLActivateEffect*>();
	for each (xpath_node xnode in objectNode.select_nodes("Activate")) {
		activateEffects->push_back(new XMLActivateEffect(xnode.node()));
	}

	projectiles = new std::unordered_map<int, XMLProjectile*>();
	for each (xpath_node xnode in objectNode.select_nodes("Projectile")) {
		XMLProjectile proj(xnode.node());
		projectiles->insert(std::make_pair(proj.id, &proj));
	}
}

#include "XMLProjectile.h"
#include "XMLConditionEffect.h"

XMLProjectile::XMLProjectile(xml_node projectileNode) {
	id = projectileNode.attribute("id").as_int();
	objectId = projectileNode.select_node("ObjectId").node().text().as_string();
	lifetimeMS = projectileNode.select_node("LifetimeMS").node().text().as_int();
	speed = projectileNode.select_node("Speed").node().text().as_int();
	size = projectileNode.select_node("Size").node().text().as_int(100);
	if (XNODE_EXISTS(projectileNode.select_node("Damage"))) {
		int damage = projectileNode.select_node("Damage").node().text().as_int();
		minDamage = damage;
		maxDamage = damage;
	}
	else {
		minDamage = projectileNode.select_node("MinDamage").node().text().as_int();
		maxDamage = projectileNode.select_node("MaxDamage").node().text().as_int();
	}
	multiHit = XNODE_EXISTS(projectileNode.select_node("MultiHit"));
	passesCover = XNODE_EXISTS(projectileNode.select_node("PassesCover"));
	armorPiercing = XNODE_EXISTS(projectileNode.select_node("ArmorPiercing"));
	particleTrail = XNODE_EXISTS(projectileNode.select_node("ParticleTrail"));
	wavy = XNODE_EXISTS(projectileNode.select_node("Wavy"));
	parametric = XNODE_EXISTS(projectileNode.select_node("Parametic"));
	boomerang = XNODE_EXISTS(projectileNode.select_node("Boomerang"));

	amplitude = projectileNode.select_node("Amplitude").node().text().as_float();
	frequency = projectileNode.select_node("Frequency").node().text().as_float(1);
	magnitude = projectileNode.select_node("Magnitude").node().text().as_float(3);

	effects = new std::vector<XMLConditionEffect*>();

	for each (xpath_node xnode in projectileNode.select_nodes("ConditionEffect")) {
		effects->push_back(new XMLConditionEffect(xnode.node()));
	}
}

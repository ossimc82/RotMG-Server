#ifndef XMLCONDITIONEFFECT_H_
#define XMLCONDITIONEFFECT_H_

#define CE_NOTHING			0
#define CE_QUIET			1
#define CE_WEAK				2
#define CE_SLOWED			3
#define CE_SICK				4
#define CE_DAZED			5
#define CE_STUNNED			6
#define CE_BLIND			7
#define CE_HALLUCINATING	8
#define CE_DRUNK			9
#define CE_CONFUSED			10
#define CE_STUN_IMMUNE		11
#define CE_INVISIBLE		12
#define CE_PARALYZED		13
#define CE_SPEEDY			14
#define CE_BLEEDING			15
#define CE_NOT_USED			16
#define CE_HEALING			17
#define CE_DAMAGING			18
#define CE_BERSERK			19
#define CE_PAUSED			20
#define CE_STASIS			21
#define CE_STASIS_IMMUNE	22
#define CE_INVINCIBLE		23
#define CE_INVULNERABLE		24
#define CE_ARMORED			25
#define CE_ARMOR_BROKEN		26
#define CE_HEXED			27
#define CE_NINJA_SPEEDY		28

#include <string>
#include <unordered_map>
#include "pugixml.hpp"

using pugi::xml_node;
using pugi::xpath_node;
using pugi::xml_attribute;
using pugi::xml_node_type;

class XMLConditionEffect {
public:
	XMLConditionEffect(xml_node conditionEffectNode);
	~XMLConditionEffect() { }

	int effect;
	double duration;
	double range;
	int target;

	static std::unordered_map<std::string, int>* conditionEffectNameMap;
private:

};

#endif // !XMLCONDITIONEFFECT_H_

#include "XMLConditionEffect.h"

using std::unordered_map;
using std::string;
using std::make_pair;

unordered_map<string, int>* XMLConditionEffect::conditionEffectNameMap;

XMLConditionEffect::XMLConditionEffect(xml_node conditionEffectNode) {
	if (conditionEffectNameMap == NULL) {
		conditionEffectNameMap = new unordered_map<string, int>();
		conditionEffectNameMap->insert(make_pair("Nothing", CE_NOTHING));
		conditionEffectNameMap->insert(make_pair("Quiet", CE_QUIET));
		conditionEffectNameMap->insert(make_pair("Weak", CE_WEAK));
		conditionEffectNameMap->insert(make_pair("Slowed", CE_SLOWED));
		conditionEffectNameMap->insert(make_pair("Sick", CE_SICK));
		conditionEffectNameMap->insert(make_pair("Dazed", CE_DAZED));
		conditionEffectNameMap->insert(make_pair("Stunned", CE_STUNNED));
		conditionEffectNameMap->insert(make_pair("Blind", CE_BLIND));
		conditionEffectNameMap->insert(make_pair("Hallucinating", CE_HALLUCINATING));
		conditionEffectNameMap->insert(make_pair("Drunk", CE_DRUNK));
		conditionEffectNameMap->insert(make_pair("Confused", CE_CONFUSED));
		conditionEffectNameMap->insert(make_pair("Stun Immune", CE_STUN_IMMUNE));
		conditionEffectNameMap->insert(make_pair("Invisible", CE_INVISIBLE));
		conditionEffectNameMap->insert(make_pair("Paralyzed", CE_PARALYZED));
		conditionEffectNameMap->insert(make_pair("Speedy", CE_SPEEDY));
		conditionEffectNameMap->insert(make_pair("Bleeding", CE_BLEEDING));
		conditionEffectNameMap->insert(make_pair("NotUsed", CE_NOT_USED));
		conditionEffectNameMap->insert(make_pair("Healing", CE_HEALING));
		conditionEffectNameMap->insert(make_pair("Damaging", CE_DAMAGING));
		conditionEffectNameMap->insert(make_pair("Berserk", CE_BERSERK));
		conditionEffectNameMap->insert(make_pair("Paused", CE_PAUSED));
		conditionEffectNameMap->insert(make_pair("Stasis", CE_STASIS));
		conditionEffectNameMap->insert(make_pair("Stasis Immune", CE_STASIS_IMMUNE));
		conditionEffectNameMap->insert(make_pair("Invincible", CE_INVINCIBLE));
		conditionEffectNameMap->insert(make_pair("Invulnerable", CE_INVULNERABLE));
		conditionEffectNameMap->insert(make_pair("Armored", CE_ARMORED));
		conditionEffectNameMap->insert(make_pair("Armor Broken", CE_ARMOR_BROKEN));
		conditionEffectNameMap->insert(make_pair("Hexed", CE_HEXED));
		conditionEffectNameMap->insert(make_pair("Ninja Speedy", CE_NINJA_SPEEDY));
	}

	effect = conditionEffectNameMap->at(conditionEffectNode.text().as_string());
	duration = conditionEffectNode.attribute("duration").as_double();
	range = conditionEffectNode.attribute("range").as_double();
	target = conditionEffectNode.attribute("target").as_int();
}

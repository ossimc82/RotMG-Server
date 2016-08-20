#ifndef STAT_H_
#define STAT_H_

#include <string>

#define MAX_HP_STAT					0
#define HP_STAT						1
#define SIZE_STAT					2
#define MAX_MP_STAT					3
#define MP_STAT						4
#define NEXT_LEVEL_EXP_STAT			5
#define EXP_STAT					6
#define LEVEL_STAT					7
#define ATTACK_STAT					20
#define DEFENSE_STAT				21
#define SPEED_STAT					22
#define INVENTORY_0_STAT			8
#define INVENTORY_1_STAT			9
#define INVENTORY_2_STAT			10
#define INVENTORY_3_STAT			11
#define INVENTORY_4_STAT			12
#define INVENTORY_5_STAT			13
#define INVENTORY_6_STAT			14
#define INVENTORY_7_STAT			15
#define INVENTORY_8_STAT			16
#define INVENTORY_9_STAT			17
#define INVENTORY_10_STAT			18
#define INVENTORY_11_STAT			19
#define RANK_ICON_STAT				25
#define VITALITY_STAT				26
#define WISDOM_STAT					27
#define DEXTERITY_STAT				28
#define CONDITION_STAT				29
#define NUM_STARS_STAT				30
#define NAME_STAT					31
#define TEX1_STAT					32
#define TEX2_STAT					33
#define MERCHANDISE_TYPE_STAT		34
#define CREDITS_STAT				35
#define MERCHANDISE_PRICE_STAT		36
#define ACTIVE_STAT					37
#define ACCOUNT_ID_STAT				38
#define FAME_STAT					39
#define MERCHANDISE_CURRENCY_STAT	40
#define CONNECT_STAT				41
#define MERCHANDISE_COUNT_STAT		42
#define MERCHANDISE_MINS_LEFT_STAT	43
#define MERCHANDISE_DISCOUNT_STAT	44
#define MERCHANDISE_RANK_REQ_STAT	45
#define MAX_HP_BOOST_STAT			46
#define MAX_MP_BOOST_STAT			47
#define ATTACK_BOOST_STAT			48
#define DEFENSE_BOOST_STAT			49
#define SPEED_BOOST_STAT			50
#define VITALITY_BOOST_STAT			51
#define WISDOM_BOOST_STAT			52
#define DEXTERITY_BOOST_STAT		53
#define OWNER_ACCOUNT_ID_STAT		54
#define RANK_REQUIRED_STAT			55
#define NAME_CHOSEN_STAT			56
#define CURR_FAME_STAT				57
#define NEXT_CLASS_QUEST_FAME_STAT	58
#define LEGENDARY_RANK_STAT			59
#define SINK_LEVEL_STAT				60
#define ALT_TEXTURE_STAT			61
#define GUILD_NAME_STAT				62
#define GUILD_RANK_STAT				63
#define BREATH_STAT					64
#define XP_BOOSTED_STAT				65
#define XP_TIMER_STAT				66
#define LD_TIMER_STAT				67
#define LT_TIMER_STAT				68
#define HEALTH_POTION_STACK_STAT	69
#define MAGIC_POTION_STACK_STAT		70
#define BACKPACK_0_STAT				71
#define BACKPACK_1_STAT				72
#define BACKPACK_2_STAT				73
#define BACKPACK_3_STAT				74
#define BACKPACK_4_STAT				75
#define BACKPACK_5_STAT				76
#define BACKPACK_6_STAT				77
#define BACKPACK_7_STAT				78
#define HASBACKPACK_STAT			79
#define TEXTURE_STAT				80

class MessageDataWriter;

class Stat {
public:
	Stat(){}
	~Stat(){}

	unsigned char	statType;
	std::string		stringValue;
	int				intValue;

	bool isStringStat();
	void writeToOutput(MessageDataWriter* wtr);
};

#endif // !STAT_H_

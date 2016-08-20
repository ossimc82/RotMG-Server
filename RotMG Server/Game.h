#ifndef GAME_H_
#define GAME_H_

#include "pugixml.hpp"
#include <unordered_map>

using pugi::xml_node;
using pugi::xpath_node;
using std::string;
using std::unordered_map;
using std::vector;
using std::make_pair;

class XMLEnemy;
class XMLItem;
class XMLWorld;
class XML;

static class Game {
public:
	static void LoadXmls();
	static std::string ObjectIdFromType(const int type);
	static std::string DisplayIdFromType(const int type);
	static int ObjectTypeFromId(const char* id);
	static vector<int> EnemyTypesFromGroup(const char* group);
	static int GroundTypeFromId(const char* id);
	static XMLWorld* WorldFromId(const char* id);
private:
	static void loadXml(const char* fileName);
	static void loadObjects(XML* curr);
	static void loadGrounds(XML* curr);
	static void loadDungeons(XML* curr);
	static unordered_map<string, int>* idToType;
	static unordered_map<string, vector<XMLEnemy*>*>* enemyGroups;
	static unordered_map<int, XMLEnemy*>* enemies;
	static unordered_map<int, xml_node*>* xmlLibrary;
	static unordered_map<int, XMLItem*>* items;
	static unordered_map<string, int>* groundIdToType;
	static unordered_map<string, XMLWorld*>* idToWorld;
	//static unordered_map<string, int> idToType;
	//static unordered_map<string, int> idToType;
	//static unordered_map<string, int> idToType;
	//static unordered_map<string, int> idToType;
	//static unordered_map<string, int> idToType;
};

#endif // !GAME_H_

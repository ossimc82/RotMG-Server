#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <string>
#include <unordered_map>
#include <unordered_set>

class Stat;
class World;

class GameObject {
public:
	GameObject();
	~GameObject();

	std::string name();
	void setName(std::string name);
	std::unordered_set<int>* updatedStats;
	int type;
	int id;

	std::string idName();
	World* game();
	void setGame(World* game);
protected:
	std::unordered_map<int, Stat*>* stats;
	Stat* getObjectStat(unsigned int type);
private:
	World* m_game;
};

#endif // !GAMEOBJECT_H_

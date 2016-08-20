#ifndef REALMMANAGER_H_
#define REALMMANAGER_H_

#include <unordered_map>

class World;
class LogicLoop;
class Player;
class MapInfoMessage;

class RealmManager
{
public:
	RealmManager();
	~RealmManager();
	std::unordered_map<int, World*>* worlds;
	void start();
	static RealmManager* instance;
	static MapInfoMessage* RegisterPlayerInWorld(int gameId, Player* player);
private:
	LogicLoop* logicLoop;
};

#endif // !REALMMANAGER_H_

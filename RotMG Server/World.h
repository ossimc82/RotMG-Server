#ifndef WORLD_H_
#define WORLD_H_

#include <string>
#include <unordered_map>

#define TR_NONE 0

class MapInfoMessage;
class XMLWorld;

class Tile {
public:
	Tile() { }
	~Tile() { }
	int x;
	int y;
	int z;
	int tileType;
	int tileRegion;
	std::string tileObj;
	std::string name;
private:

};

class GameObject;

class World
{
public:
	World(const char* xmlId);
	~World();
	void update(double time, double dt);
	std::unordered_map<int, GameObject> gameObjs;
	bool isLimbo;
	MapInfoMessage* mapInfo();
	void buildMap();

	XMLWorld* xmlWorld;

	void setTile(int x, int y, Tile tile);

	int							width;
	int							height;
	const char*					name;
	const char*					displayName;
	int							difficulty;
	unsigned int				fp;
	int							background;
	bool						allowPlayerTeleport;
	bool						showDisplays;

private:
	std::vector<Tile*>* tiles;
};

#endif // !WORLD_H_

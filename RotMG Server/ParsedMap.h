#ifndef PARSEDMAP_H_
#define PARSEDMAP_H_

#include "json.hpp"
#include "Util.h"
#include <zlib.h>
#include <unordered_map>

using nlohmann::json;
using nlohmann::basic_json;

class World;
class Tile;

struct obj {
public:
	std::string name;
	std::string id;

	void parse(basic_json<> j);
};

struct loc {
public:
	std::string ground;
	std::vector<obj> objs;
	std::vector<obj> regions;

	void parse(basic_json<> j);
};

struct json_dat {
public:
	std::string data;
	int width;
	int height;
	std::vector<loc> dict;

	void parse(basic_json<> j);
};

class ParsedMap {
public:
	ParsedMap(const char* json);
	~ParsedMap() { }

	void addToMapCenter(World* target, float x, float y);
	static ParsedMap* ParseFromFile(const char* file);
private:
	json_dat dat;
	std::unordered_map<short, Tile>* tileDict;
	std::vector<Tile>* map;
};

#endif // !PARSEDMAP_H_

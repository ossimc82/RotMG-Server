#include "ParsedMap.h"
#include "World.h"
#include <iostream>
#include <fstream>
#include "MessageDataReader.h"
#include "Game.h"

using nlohmann::json;

ParsedMap::ParsedMap(const char* json) {
	auto mapJson = json::parse(json);
	dat.parse(mapJson);

	tileDict = new unordered_map<short, Tile>();

	for (size_t i = 0; i < dat.dict.size(); i++) {
		loc o = dat.dict[i];

		Tile t;
		t.tileObj = o.objs.size() == 0 ? "" : o.objs[0].id;
		t.tileType = o.ground.empty() ? 0xFF : Game::GroundTypeFromId(o.ground.c_str());
		t.name = o.objs.size() == 0 ? "" : (o.objs[0].name.empty() ? "" : o.objs[0].name);
		//t.tileRegion = o.regions.size() == 0 ? TR_NONE : Tile::RegionNameToId(o.regions[0].id);
		tileDict->insert(make_pair(i, t));
	}

	map = new vector<Tile>();
	MessageDataReader* rdr = new MessageDataReader(dat.data.c_str(), dat.data.size());
	for (size_t y = 0; y < dat.height; y++) {
		for (size_t x = 0; x < dat.width; x++) {
			int16_t val = rdr->readInt16();
			map->push_back(tileDict->at(val));
		}
	}
}

void ParsedMap::addToMapCenter(World* target, float x, float y) {
	for (int dx = 0; dx < dat.width; dx++) {
		for (int dy = 0; dy < dat.height; dy++) {
			Tile tile = map->at(dx + dy * dat.width);
			target->setTile((x + dx) - (dat.width / 2), (y + dy) - (dat.height / 2), tile);
		}
	}
}

ParsedMap* ParsedMap::ParseFromFile(const char* file) {
	std::ifstream ifs(file);
	std::string content = std::string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
	const char* json = content.c_str();
	return new ParsedMap(json);
}

void json_dat::parse(basic_json<> j) {
	std::string compr = Util::base64_decode(j["data"].get<std::string>());
	unsigned char* buffer = reinterpret_cast<unsigned char*>((char*)compr.c_str());
	data = Util::decompress_zlib(buffer, compr.size());

	width = j["width"].get<int>();
	height = j["height"].get<int>();

	for (int i = 0; i < j["dict"].size(); i++) {
		loc l;
		l.parse(j["dict"].at(i));
		dict.push_back(l);
	}
}

void loc::parse(basic_json<> j) {
	ground = j["ground"].get<std::string>();

	for (size_t i = 0; i < j["objs"].size(); i++) {
		obj o;
		o.parse(j["objs"].at(i));
		objs.push_back(o);
	}

	for (size_t i = 0; i < j["regions"].size(); i++) {
		obj o;
		o.parse(j["regions"].at(i));
		regions.push_back(o);
	}
}

void obj::parse(basic_json<> j) {
	name = j["name"].get<std::string>();
	id = j["id"].get<std::string>();
}

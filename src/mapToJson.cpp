#include "mapToJson.h"
#include "mapCollect.h"


using json = nlohmann::json;


void mapFileToJsonFile(const std::string& mapFileName, const std::string& outputFileName) {
	auto map = Map::ReadMap(mapFileName);
	map.TrimTilesetSources();
	auto json = mapToJson(map);

	Stream::FileWriter outFile(outputFileName);
	outFile.Write(json.dump(2));
	// outFile.Write(json.dump());
	outFile.Write("\n");
}

json mapToJson(const Map& map) {
	json j;

	auto width = map.WidthInTiles();
	auto height = map.HeightInTiles();
	j["header"]["width"] = width;
	j["header"]["height"] = height;
	j["tiles"] = mapCollect(map.tiles, [](Tile tile) { return tile.tileMappingIndex; });
	// Optionally store clip rect if it is not the expected default
	if (!isDefaultClipRect(map.clipRect, width, height)) {
		//std::cerr << "Non-default clip rect" << std::endl;
		j["clipRect"] = map.clipRect;
	}
	// Optionally include tileset information
	j["tileset"] = tilesetToJson(map);

	return j;
}

json tilesetToJson(const Map& map) {
	json j;
	// Tileset
	j["sources"] = map.tilesetSources;
	// mapCollect(map.tilesetSources, [](TilesetSource source) {
	// 	return json{{"filename", source.tilesetFilename}, {"numTiles", source.numTiles}};
	// });
	j["tileMappings"] = map.tileMappings;
	j["terrainTypes"] = map.terrainTypes;
	//map.tileGroups;

	return j;
}

bool isDefaultClipRect(const Rect& clipRect, int width, int height) {
	return clipRect == defaultClipRect(width, height);
}

Rect defaultClipRect(int width, int height) {
	int x = (width < 512) ? 32 : 0;
	return Rect{ x, 0, x + width - 1, height - 2 };
}

void to_json(json& j, const Rect& rect) {
	j = json{
		{"x1", rect.x1},
		{"y1", rect.y1},
		{"x2", rect.x2},
		{"y2", rect.y2}
	};
}

void to_json(json& j, const TilesetSource& tilesetSource) {
	j = json{
		{"filename", tilesetSource.tilesetFilename},
		{"numTiles", tilesetSource.numTiles}
	};
}

void to_json(json& j, const TileMapping& tileMapping) {
	j = json{
		{"tilesetIndex", tileMapping.tilesetIndex},
		{"tileGraphicIndex", tileMapping.tileGraphicIndex},
		{"animationCount", tileMapping.animationCount},
		{"animationDelay", tileMapping.animationDelay}
	};
}

void to_json(json& j, const Range16& range) {
	j = json{
		{"start", range.start},
		{"end", range.end}
	};
}

void to_json(json& j, const TerrainType& terrainType) {
	j = json{
		{"tileRange", terrainType.tileMappingRange},
		{"bulldozedTileMappingIndex", terrainType.bulldozedTileMappingIndex},
		{"rubbleTileMappingIndex", terrainType.rubbleTileMappingIndex},
		{"tubeTileMappings", terrainType.tubeTileMappings},
		{"wallTileMappingIndexes", terrainType.wallTileMappingIndexes},
		{"lavaTileMappingIndex", terrainType.lavaTileMappingIndex},
		{"flat1", terrainType.flat1},
		{"flat2", terrainType.flat2},
		{"flat3", terrainType.flat3},
		{"tubeTileMappingIndexes", terrainType.tubeTileMappingIndexes},
		{"scorchedTileMappingIndex", terrainType.scorchedTileMappingIndex},
		{"scorchedRange", terrainType.scorchedRange},
		{"unknown", terrainType.unknown},
	};
}


// template<typename T>
// void to_json(json& j, const std::vector<T>& vector) {
// 	j = json{
// 		mapCollect(vector, [](T item) {
// 			return json{item};
// 		})
// 	};
// }

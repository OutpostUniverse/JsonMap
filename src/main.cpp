#include "mapToJson.h"
#include "mapCollect.h"
#include <iostream>

using json = nlohmann::json;


void mapFileToJsonFile(const std::string& mapFileName, const std::string& outputFileName) {
	auto map = MapReader::ReadMap(mapFileName);
	map.TrimTilesetSources();
	auto json = mapToJson(map);

	Stream::FileWriter outFile(outputFileName);
	outFile.Write(json.dump(2));
	// outFile.Write(json.dump());
	outFile.Write("\n");
}


json mapToJson(const MapData& map) {
	json j;

	auto width = map.header.MapTileWidth();
	auto height = map.header.mapTileHeight;
	j["header"]["width"] = width;
	j["header"]["height"] = height;
	j["tiles"] = mapCollect(map.tiles, [](TileData tileData) { return tileData.tileIndex; });
	// Optionally store clip rect if it is not the expected default
	if (!isDefaultClipRect(map.clipRect, width, height)) {
		//std::cerr << "Non-default clip rect" << std::endl;
		j["clipRect"] = map.clipRect;
	}
	// Optionally include tileset information
	j["tileset"] = tilesetToJson(map);

	return j;
}

json tilesetToJson(const MapData& map) {
	json j;
	// Tileset
	j["sources"] = map.tilesetSources;
	// mapCollect(map.tilesetSources, [](TilesetSource source) {
	// 	return json{{"filename", source.tilesetFilename}, {"numTiles", source.numTiles}};
	// });
	j["tileInfos"] = map.tileInfos;
	j["terrainTypes"] = map.terrainTypes;
	//map.tileGroups;

	return j;
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

void to_json(json& j, const TileInfo& tileInfo) {
	j = json{
		{"tilesetIndex", tileInfo.tilesetIndex},
		{"tileIndex", tileInfo.tileIndex},
		{"animationCount", tileInfo.animationCount},
		{"animationDelay", tileInfo.animationDelay}
	};
}

void to_json(json& j, const TileRange& tileRange) {
	j = json{
		{"start", tileRange.start},
		{"end", tileRange.end}
	};
}

void to_json(json& j, const TerrainType& terrainType) {
	j = json{
		{"tileRange", terrainType.tileRange},
		{"bulldozedTileIndex", terrainType.bulldozedTileIndex},
		{"rubbleTileIndex", terrainType.rubbleTileIndex},
		{"tubeTiles", terrainType.tubeTiles},
		{"wall", terrainType.wall},
		{"lavaTileIndex", terrainType.lavaTileIndex},
		{"flat1", terrainType.flat1},
		{"flat2", terrainType.flat2},
		{"flat3", terrainType.flat3},
		{"tube", terrainType.tube},
		{"scorchedTileIndex", terrainType.scorchedTileIndex},
		{"scorchedRange", terrainType.scorchedRange},
		{"unkown", terrainType.unkown},
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


bool isDefaultClipRect(const Rect& clipRect, int width, int height) {
	return clipRect == defaultClipRect(width, height);
}

Rect defaultClipRect(int width, int height) {
	int x = (width < 512) ? 32 : 0;
	return Rect{x, 0, x + width - 1, height - 2};
}


int main(int argc, char* argv[]) {
	if (argc <= 1) {
		std::cout << "Usage: " << argv[0] << " mapFile1.map ..." << std::endl << std::endl;
		return 1;
	}

	const auto numArgs = static_cast<size_t>(argc);
	for (size_t i = 1; i < numArgs; ++i) {
		std::string inputFileName{argv[i]};
		std::string outputFileName{inputFileName + ".json"};
		std::cout << "Converting " << inputFileName << " to " << outputFileName << std::endl;
		mapFileToJsonFile(inputFileName, outputFileName);
	}
	return 0;
}
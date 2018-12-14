#include "OP2Utility.h"
#include <json.hpp>
#include <string>

void mapFileToJsonFile(const std::string& mapFileName, const std::string& outputFileName);
nlohmann::json mapToJson(const MapData& map);
nlohmann::json tilesetToJson(const MapData& map);
bool isDefaultClipRect(const Rect& clipRect, int width, int height);
Rect defaultClipRect(int width, int height);
void to_json(nlohmann::json& j, const Rect& rect);
void to_json(nlohmann::json& j, const TilesetSource& tilesetSource);
void to_json(nlohmann::json& j, const TileInfo& tileInfo);
void to_json(nlohmann::json& j, const TileRange& tileRange);
void to_json(nlohmann::json& j, const TerrainType& terrainType);

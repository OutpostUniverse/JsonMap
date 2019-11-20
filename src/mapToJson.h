#include "OP2Utility.h"
#if _WIN32
#include <nlohmann/json.hpp>
#else
#include <json.hpp>
#endif
#include <string>
#include <cstddef>

void mapFileToJsonFile(const std::string& mapFileName, const std::string& outputFileName);
nlohmann::json mapToJson(const Map& map);
nlohmann::json tilesetToJson(const Map& map);
bool isDefaultClipRect(const Rect& clipRect, int width, int height);
Rect defaultClipRect(int width, int height);
void to_json(nlohmann::json& j, const Rect& rect);
void to_json(nlohmann::json& j, const TilesetSource& tilesetSource);
void to_json(nlohmann::json& j, const TileMapping& tileMapping);
void to_json(nlohmann::json& j, const Range16& range);
void to_json(nlohmann::json& j, const TerrainType& terrainType);

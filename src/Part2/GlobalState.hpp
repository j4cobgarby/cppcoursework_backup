#ifndef GLOBALSTATE_HPP
#define GLOBALSTATE_HPP

#include "WorldTileManager.hpp"
#include <filesystem>

extern WorldTilesObject *worldTiles;
extern std::filesystem::path worldFolder;
extern bool newWorld;

#endif
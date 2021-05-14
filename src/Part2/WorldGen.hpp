#ifndef WORLDGEN_HPP
#define WORLDGEN_HPP

#include "WorldTileManager.hpp"
#include <vector>
#include <utility>

#define LOWEST_VALLEY   20
#define HIGHEST_PEAK    50
#define MIN_TREE_GAP    5
#define TREE_LEAVES_MINWIDTH    3
#define TREE_LEAVES_MINHEIGHT   3
#define TREE_LEAVES_VARIANCE    2
#define WORLDNOISE_OCTAVES      2
#define WORLDNOISE_FREQ         0.02

static_assert(LOWEST_VALLEY < HIGHEST_PEAK, "Mountains must be taller than valleys");

typedef std::pair<int, int> point;
typedef std::vector<point> pointvector;

class WorldGen {
public:
    static void generateWorld(int seed, WorldTileManager *front, WorldTileManager *back);
    static float perlin1dFractal(int seed, float x, int octaves, float freq);
    static int getTerrainTop(WorldTileManager *world, int x);
private:
    static float perlin1dBasic(int seed, float x);
    static float getScalarAt(int seed, int x);
    static float interp(float a, float b, float weight);

    static void placeTree(int seed, WorldTileManager *tiles, int x, int y);
    static void placeLake(int seed, WorldTileManager *foreground, WorldTileManager *background, int x);

    static pointvector getPointsInOval(int x, int y, int radx, int rady);
};

#endif
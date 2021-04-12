#include "../header.h"
#include "WorldGen.hpp"
#include "WorldTileManager.hpp"
#include <cmath>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <utility>

void WorldGen::generateWorld(int seed, WorldTileManager *front, WorldTileManager *back) {
    if (front->getMapWidth() != back->getMapWidth() || front->getMapHeight() != back->getMapHeight()) {
        std::cerr << "Unmatched tilemap dimensions" << std::endl;
        return;
    }

    int width = front->getMapWidth();
    int height = front->getMapHeight();
    int tree_gap_counter = 0;

    for (int x = 0; x < width; x++) {
        int terrain_top = height - (LOWEST_VALLEY + ((float)(HIGHEST_PEAK-LOWEST_VALLEY)/2)
            * (1+perlin1dFractal(seed, x, WORLDNOISE_OCTAVES, WORLDNOISE_FREQ)));

        if (tree_gap_counter++ >= MIN_TREE_GAP) {
            srand(seed+x);
            int r = rand() % 20;
            if (rand() % 10 == 0) {
                placeTree(seed, back, x, terrain_top-1);
                tree_gap_counter = 0;
            }
        }
        
        for (int y = terrain_top, depth = 0; y < height; y++, depth++) {
            back->setMapValue(x, y, 3);

            if (depth == 0) {
                front->setMapValue(x, y, 2);
            } else if (depth < 6) {
                front->setMapValue(x, y, 1);
            } else {
                front->setMapValue(x, y, 3);
            }
        }
    }

    for (int x = 0; x < width; x += 30 + (rand() % 30)) {
       placeLake(seed, front, back, x);
    }
}

void WorldGen::placeTree(int seed, WorldTileManager *tiles, int x, int y) {
    srand(seed+x);
    int trunk_height = 3 + (rand() % 6);
    int leaves_height = TREE_LEAVES_MINHEIGHT + 2*(rand() % TREE_LEAVES_VARIANCE);
    int leaves_width = TREE_LEAVES_MINWIDTH + 2*(rand() % TREE_LEAVES_VARIANCE);

    // Generate trunk
    for (int i = 0; i < trunk_height; i++) {
        tiles->setMapValue(x, y-i, 4);
    }

    // Place leaves
    for (int lx = x - leaves_width/2; lx < x - leaves_width/2 + leaves_width; lx++) {
        for (int ly = y-trunk_height-leaves_height; ly <= y-trunk_height; ly++) {
            tiles->setMapValue(lx, ly, 5);
        }
    }
}

void WorldGen::placeLake(int seed, WorldTileManager *foreground, WorldTileManager *background, int x) {
    srand(seed+x);
    int lake_surface = getTerrainTop(foreground, x);
    int lowest_y = 0;

    pointvector points = getPointsInOval(x, lake_surface, 4+(rand()%4), 2+(rand()%3));
    int oval_min_x = foreground->getMapWidth(), oval_max_x = 0;
    int oval_min_y = foreground->getMapHeight();

    for (point p : points) {
        if (p.first < oval_min_x) oval_min_x = p.first;
        if (p.first > oval_max_x) oval_max_x = p.first;
        if (p.second < oval_min_y) oval_min_y = p.second;
    }

    // Find the lowest terrain point in the oval
    // Water in the lake must always be at this
    // level or lower.
    // (A higher y is lower on the map)
    for (int check_x = oval_min_x-1; check_x <= oval_max_x+1; check_x++) {
        if (0 <= check_x && check_x < foreground->getMapWidth()) {
            if (getTerrainTop(foreground, check_x) > lowest_y) lowest_y = getTerrainTop(foreground, check_x);
        }
    }

    // Set water and air in lake
    for (point p : points) {
        if (p.second >= lowest_y) {
            foreground->setMapValue(p.first, p.second, 6);
        } else {
            foreground->setMapValue(p.first, p.second, 0);
        }
    }

    // Erode extra blocks above the lake
    for (int ex = oval_min_x; ex <= oval_max_x; ex++) {
        for (int ey = oval_min_y; ey < lowest_y; ey++) {
            foreground->setMapValue(ex, ey, 0);
        }
    }
}

float WorldGen::perlin1dBasic(int seed, float x) {
    int left = floor(x);
    int right = left + 1;

    float left_scalar = getScalarAt(seed, left);
    float right_scalar = getScalarAt(seed, right);

    float left_offset = (float)left - x;
    float right_offset = (float)right - x;

    float left_prod = left_scalar * left_offset;
    float right_prod = right_scalar * right_offset;

    return interp(left_prod, right_prod, x - (float)left);
}

float WorldGen::perlin1dFractal(int seed, float x, int octaves, float freq) {
    float ret = perlin1dBasic(seed, x * freq);
    float amplitude = 1;

    for (int i = 0; i < octaves; i++) {
        freq *= 2;
        amplitude /= 2;
        ret += amplitude * perlin1dBasic(seed, x*freq);
    }

    return ret;
}

float WorldGen::getScalarAt(int seed, int x) {
    srand(seed+x);
    float f = 2*((float)rand() / (float)RAND_MAX) - 1;
    return f;
}

float WorldGen::interp(float a, float b, float weight) {
    return (b - a) * (3.0 - weight * 2.0) * weight * weight + a;
}

int WorldGen::getTerrainTop(WorldTileManager *world, int x) {
    for (int y = 0; y < world->getMapHeight(); y++) {
        if (world->getMapValue(x, y) != 0) {
            return y;
        }
    }

    return world->getMapHeight() - 1;
}

pointvector WorldGen::getPointsInOval(int x, int y, int radx, int rady) {
    pointvector ret;
    int xmin = x-radx;
    int xmax = x+radx;
    int ymin = y-rady;
    int ymax = y+rady;
    int radx2 = radx * radx;
    int rady2 = rady * rady;

    for (float ix = xmin; ix <= xmax; ix += 1) {
        for (float iy = ymin; iy <= ymax; iy += 1) {
            float check = ((ix-x)*(ix-x))/radx2 + ((iy-y)*(iy-y))/rady2;
            if (check <= 1) {
                ret.push_back(std::make_pair(ix, iy));
            }
        }
    }

    return ret;
}
#include "../header.h"
#include "ExtraDrawing.hpp"


void ExtraDrawing::drawRectangleOutline(DrawingSurface *surf, int x1, int y1, int x2, int y2, unsigned int colour) {
    surf->drawLine(x1, y1, x1, y2, colour);
    surf->drawLine(x1, y2, x2, y2, colour);
    surf->drawLine(x2, y2, x2, y1, colour);
    surf->drawLine(x2, y1, x1, y1, colour);
}

void ExtraDrawing::drawRectangleThickOutline(DrawingSurface *surf, int x1, int y1, int x2, int y2, unsigned int colour, int width) {
    surf->drawThickLine(x1, y1, x1, y2, colour, width);
    surf->drawThickLine(x1, y2, x2, y2, colour, width);
    surf->drawThickLine(x2, y2, x2, y1, colour, width);
    surf->drawThickLine(x2, y1, x1, y1, colour, width);
}

void ExtraDrawing::drawDottedRectangle(DrawingSurface *surf, int x1, int y1, int x2, int y2, unsigned int colour) {
    for (int x = x1; x <= x2; x += 2) {
        surf->setPixel(x, y1, colour);
        surf->setPixel(x, y2, colour);
    }

    for (int y = y1; y <= y2; y += 2) {
        surf->setPixel(x1, y, colour);
        surf->setPixel(x2, y, colour);
    }
}
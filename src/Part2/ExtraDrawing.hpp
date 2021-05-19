#ifndef EXTRADRAWING_HPP
#define EXTRADRAWING_HPP

#include "../DrawingSurface.h"

class ExtraDrawing {
public:
    static void drawRectangleOutline(DrawingSurface *surf, int x1, int y1, int x2, int y2, unsigned int colour);
	static void drawRectangleThickOutline(DrawingSurface *surf, int x1, int y1, int x2, int y2, unsigned int colour, int width);
    static void drawDottedRectangle(DrawingSurface *surf, int x1, int y1, int x2, int y2, unsigned int colour);
};

#endif
#ifndef IMAGEMAPSCALE_HPP
#define IMAGEMAPSCALE_HPP

#include "../ImagePixelMapping.h"

class ImagePixelMappingScale : public ImagePixelMapping {
public:
    ImagePixelMappingScale(double sx, double sy) : sx(sx), sy(sy) {
    }

    virtual bool mapCoordinates(double &x, double &y, const SimpleImage &image) override {
        y *= sy;
        x *= sx;
        return true;
    }
protected:
    double sx, sy;
};

#endif
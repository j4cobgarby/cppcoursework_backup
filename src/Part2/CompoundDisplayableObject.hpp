#ifndef COMPOUNDDISPLAYABLEOBJECT_HPP
#define COMPOUNDDISPLAYABLEOBJECT_HPP

#include "../DisplayableObject.h"
#include <array>

#define SLIME_COUNT 10

class CompoundDisplayableObject : DisplayableObject { 
protected:
    std::array<DisplayableObject *, SLIME_COUNT> objs;
public:
    

    void virtDraw() override;
};

#endif
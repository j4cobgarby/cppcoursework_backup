#ifndef FOLLOWER_HPP
#define FOLLOWER_HPP

#include "BaseEngine.h"
#include "DisplayableObject.h"

class FollowerObject : public DisplayableObject {
private:
    const float movementSpeed = 1;
    float fX;
    float fY;
    DisplayableObject *toFollow;
public:
    FollowerObject(BaseEngine *eng, float x, float y, DisplayableObject *toFollow)
        : DisplayableObject(eng), toFollow(toFollow) {
        fX = x;
        fY = y;
        m_iCurrentScreenX = x;
        m_iCurrentScreenY = y;
        m_iDrawWidth = m_iDrawHeight = 60;

        setVisible(true);
    }

    void virtDraw() override;
    
    void virtDoUpdate(int iCurrentTime) override;
};

#endif
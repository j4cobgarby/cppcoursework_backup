#include "header.h"
#include "Follower.hpp"
#include "UtilCollisionDetection.h"
#include <math.h>

void FollowerObject::virtDraw() {
    getEngine()->drawForegroundOval(
        m_iCurrentScreenX,
        m_iCurrentScreenY,
        m_iCurrentScreenX + m_iDrawWidth,
        m_iCurrentScreenY + m_iDrawHeight,
        0xff0000);
}

void FollowerObject::virtDoUpdate(int iCurrentTime) {
    float dx = toFollow->getXCentre() - (int)(m_iCurrentScreenX + m_iDrawWidth/2);
    float dy = toFollow->getYCentre() - (int)(m_iCurrentScreenY + m_iDrawHeight/2);
    
    float mag = sqrtf(dx*dx + dy*dy);

    if (mag >= 0.001) {
        dx /= mag;
        dy /= mag;
    }

    dx *= movementSpeed;
    dy *= movementSpeed;

    if (!CollisionDetection::checkCircles(toFollow->getXCentre(), toFollow->getYCentre(), 
            fX+dx + (float)m_iDrawWidth/2, fY+dy + (float)m_iDrawHeight/2, 55)) {
        fX += dx;
        fY += dy;

        m_iCurrentScreenX = (int)fX;
        m_iCurrentScreenY = (int)fY;
    }
}
#ifndef COLLISIONSHAPE_HPP
#define COLLISIONSHAPE_HPP

class CollisionShape {
protected:
    float x, y;
public:
    virtual float getBoundsX();
    virtual float getBoundsY();
    virtual float getX();
    virtual float getY();
    virtual float getCenterX();
    virtual float getCenterY();
};

class CircleShape : public CollisionShape {
protected:
    float rad;
public:
    CircleShape(float x, float y, float rad)
        : rad(rad) {
        this->x = x;
        this->y = y;
    }

    float getRad() {return rad;}
};

class Collisions {
public:
    static bool overlaps(CircleShape &s1, CircleShape &s2) {
        return ((s1.getX()-s2.getX())*(s1.getX()-s2.getX())
            + (s1.getY()-s2.getY())*(s1.getY()-s2.getY()))
            <= (s1.getRad()+s2.getRad())*(s1.getRad()+s2.getRad());
    }
};

#endif
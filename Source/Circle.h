//
// Created by jon on 25/05/19.
//

#ifndef EVOWORLD_CIRCLE_H
#define EVOWORLD_CIRCLE_H


#include "Math.h"

class Circle {
public:
    Circle(const Vec2& initPosition, float initRadius);

    inline const Vec2 & getPosition() const {return _position;}
    inline void setPosition(const Vec2& position) { _position = position;}

    inline float getRadius() const { return _radius; }
    inline void setRadius(float radius) { _radius = radius;}

    inline bool overlaps(const Circle & other) const {
        const sf::Vector2f diff = other.getPosition() - getPosition();
        const float sumOfRadii = getRadius() + other.getRadius();
        return (diff.x * diff.x + diff.y * diff.y) <= (sumOfRadii * sumOfRadii);
    }
private:
    Vec2 _position;
    float _radius = 0.f;
};


#endif //EVOWORLD_CIRCLE_H

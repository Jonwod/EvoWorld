#ifndef CIRCLEBODY_H
#define CIRCLEBODY_H
#include "SFML/System/Vector2.hpp"
#include "Math.h"


class CircleBody{
public:
    CircleBody(float radius, float mass, sf::Vector2f initPosition = sf::Vector2f(0.f, 0.f));

    inline float getRadius() const { return _radius; }
    inline void setRadius(float radius) { _radius = radius;}

    // Updates position based on velocity
    void update(float dt);

    inline const Vec2 & getPosition() const {return _position;}
    inline void setPosition(const Vec2& position) { _position = position;}

    const Vec2& getVelocity() const;

    void setVelocity(const Vec2& velocity);

    inline bool overlaps(const CircleBody & other) const {
        const sf::Vector2f diff = other.getPosition() - getPosition();
        const float sumOfRadii = getRadius() + other.getRadius();
        return (diff.x * diff.x + diff.y * diff.y) <= (sumOfRadii * sumOfRadii);
    }

private:
    float _radius = 0.f;
    float _mass = 1.f;
    Vec2 _position;
    Vec2 _velocity;
};


#endif // CIRCLEBODY_H

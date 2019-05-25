#ifndef CIRCLEBODY_H
#define CIRCLEBODY_H
#include "SFML/System/Vector2.hpp"
#include "Math.h"
#include "Circle.h"


class CircleBody: public Circle{
public:
    CircleBody(float radius, float mass, sf::Vector2f initPosition = sf::Vector2f(0.f, 0.f));

    // Updates position based on velocity
    void update(float dt);

    const Vec2& getVelocity() const;

    void setVelocity(const Vec2& velocity);

private:
    float _mass = 1.f;
    Vec2 _velocity;
};


#endif // CIRCLEBODY_H

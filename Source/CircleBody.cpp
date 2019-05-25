#include "CircleBody.h"


CircleBody::CircleBody(float radius, float mass, Vec2 initPosition)
    :Circle(initPosition, radius),
    _mass(mass)
{
    // ...
}


const Vec2& CircleBody::getVelocity() const {
    return _velocity;
}


void CircleBody::setVelocity(const Vec2& velocity) {
    _velocity = velocity;
}


void CircleBody::update(float dt){
    setPosition(getPosition() + _velocity * dt);
}
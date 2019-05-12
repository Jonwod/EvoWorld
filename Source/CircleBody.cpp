#include "CircleBody.h"


CircleBody::CircleBody(float radius, float mass, Vec2 initPosition)
    :_radius(radius),
    _position(initPosition),
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
    _position += _velocity * dt;
}
//
// Created by jon on 25/05/19.
//

#include "Plant.h"

Plant::Plant(const Vec2 &initPosition)
    :_position(initPosition)
{
    //...
}


void Plant::draw(sf::RenderWindow &renderWindow) const {
    sf::CircleShape circle{_radius};
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setFillColor(_color);
    circle.setPosition(_position);
    renderWindow.draw(circle);
}


float Plant::getEnergy() const{
    return _radius;
}


float Plant::consume() {
    const float energy = getEnergy();
    _radius = 0.f;
    return energy;
}


Circle Plant::getCircle() {
    return Circle(_position, _radius);
}

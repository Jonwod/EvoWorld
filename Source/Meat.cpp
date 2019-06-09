//
// Created by jon on 08/06/19.
//

#include "Meat.h"


Meat::Meat(const Vec2 &position, const float radius, const sf::Color &color)
    :_position(position),
    _radius(radius),
    _color(color)
{
    //...
}


void Meat::draw(sf::RenderWindow &renderWindow) const {
    sf::CircleShape circle{_radius};
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setFillColor(_color);
    circle.setOutlineThickness(1.f);
    circle.setPosition(_position);

    renderWindow.draw(circle);
}


float Meat::consume() {
    const float energy = getEnergy();
    _radius = 0.f;
    return energy;;
}



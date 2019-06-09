//
// Created by jon on 08/06/19.
//

#ifndef EVOWORLD_MEAT_H
#define EVOWORLD_MEAT_H
#include "Math.h"
#include "SFML/Graphics.hpp"

class Meat {
public:
    Meat(const Vec2 & position, const float radius, const sf::Color& color);

    bool isDestroyed() const { return _radius <= 0; };

    // Returns the energy granted to the consumer, then destroys self
    float consume();

    const Vec2 & getPosition() const {return _position;};

    float getRadius() const {return _radius;}

    void draw(sf::RenderWindow & renderWindow) const;
private:
    float getEnergy() const { return _radius * 2.f; }

    Vec2 _position;
    float _radius = 0.f;
    sf::Color _color;
};


#endif //EVOWORLD_MEAT_H

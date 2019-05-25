//
// Created by jon on 25/05/19.
//

#ifndef EVOWORLD_PLANT_H
#define EVOWORLD_PLANT_H
#include "SFML/Graphics.hpp"
#include "Math.h"
#include "Circle.h"


class Plant {
public:
    Plant(const Vec2& initPosition);

    void draw(sf::RenderWindow & renderWindow) const;

    // Returns the energy granted to the consumer and renders this plant dead
    float consume();

    inline bool isAlive() const { return _radius > 0.f;};

    Circle getCircle();
private:
    float getEnergy() const;

    Vec2 _position;
    float _radius{12.f};
    sf::Color _color{125, 125, 0};
};


#endif //EVOWORLD_PLANT_H

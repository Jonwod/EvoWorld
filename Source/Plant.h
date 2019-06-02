//
// Created by jon on 25/05/19.
//

#ifndef EVOWORLD_PLANT_H
#define EVOWORLD_PLANT_H
#include "SFML/Graphics.hpp"
#include "Math.h"
#include "Circle.h"


//Gains nutrition though photosynthesis (passively)
class Plant{
public:
    Plant();
    inline void setPosition(sf::Vector2f newPosition){ _position = newPosition; }
    inline sf::Vector2f getPosition() const { return _position; }

    void update(float deltaT);

    void draw(sf::RenderWindow & renderWindow) const;

    //Pre-compilation settings
    //When nutrition level reaches level, plant can reproduce
    constexpr static const float energyRequiredToReproduce = 15.0f;
    constexpr static const float photosynthesisRate = 1.75f;
    //will vary photosynthesis per frame by this value in either direction
    constexpr static const float photosynthesisRateRandomDrift = 0.1f;
    //The radius (or perhaps square) within which offspring will spawn randomly
    constexpr static const int offspringSpawnRadius = 300;

    inline float getRadius() const { return _radius;}

    inline void setEnergy(float energy) { _radius = energy;}

    inline bool isAlive() const { return getRadius()  > 0.f;};

    void die();

    // Returns the energy granted to the consumer and renders this plant dead
    float consume();

    Circle getCircle() const;
private:
    float getEnergy() const { return getRadius(); }

    void reproduce();

    void addEnergy(float energyToAdd);

    float _radius = 12.f;
    Vec2 _position;
};


#endif //EVOWORLD_PLANT_H

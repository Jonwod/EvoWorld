//
// Created by jon on 25/05/19.
//

#include "Plant.h"
#include "World.h"


Plant::Plant(){

}


void Plant::update(float deltaT){
    const float photosynthAdd = photosynthesisRate * deltaT;
    addEnergy(photosynthAdd + photosynthAdd * randFloat(-photosynthesisRateRandomDrift, photosynthesisRateRandomDrift));

    if(getEnergy() >= energyRequiredToReproduce){
        reproduce();
    }
}


void Plant::draw(sf::RenderWindow &renderWindow) const{
    sf::CircleShape visualShape;
    visualShape.setRadius(getEnergy());
    visualShape.setFillColor({17,255,12,230});
    visualShape.setOutlineThickness(2);
    visualShape.setOutlineColor({0,0,0,255});
    visualShape.setPosition(_position);
    visualShape.setOrigin(visualShape.getRadius(), visualShape.getRadius());
    renderWindow.draw(visualShape);
}


void Plant::reproduce(){
    Plant offspring{};
    //I can't remember if my rand function works for negative ranges
    const int randX = randInt( 0, 2 * offspringSpawnRadius) - offspringSpawnRadius;
    const int randY = randInt( 0, 2 * offspringSpawnRadius) - offspringSpawnRadius;
    offspring.setPosition(getPosition() + sf::Vector2f(randX, randY));
    offspring.setEnergy(getEnergy()/2);
    World::get().spawnPlant(offspring);
    setEnergy(getEnergy() / 2.0f);
}


float Plant::consume() {
    const float energy = getEnergy();
    setEnergy(0.f);
    return energy;
}


void Plant::addEnergy(float energyToAdd) {
    setEnergy(getEnergy() + energyToAdd);
}


Circle Plant::getCircle() const {
    return {getPosition(), getRadius()};
}


void Plant::die() {
    setEnergy(0.f);
}

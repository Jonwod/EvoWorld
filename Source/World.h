//
// Created by jon on 25/05/19.
//

#ifndef EVOWORLD_WORLD_H
#define EVOWORLD_WORLD_H

#include <vector>
#include "Plant.h"
#include "Snake.h"
#include "Meat.h"
#include "Math.h"


class World {
public:
    //access the instance
    inline static World & get(){
        static World instance;
        return instance;
    }

    void update(float deltaSeconds);
    void draw(sf::RenderWindow & renderWindow) const;

    // Testing
    Vec2 getTestSnakePosition() const;
    //

    void spawnPlant(const Plant & plantTemplate);

    void spawnMeat(const std::vector<Vec2> & meatPositions, float meatRadius, sf::Color color);
private:
    void checkSnakeOnSnakeOverlaps();
    void reproduce(int snakeIndex);
    void clearDead();
    std::vector<Snake> _snakes;
    std::vector<Plant> _plants;
    std::vector<Meat> _meat;
    sf::FloatRect inhabitableZone = sf::FloatRect{-5000, -5000, 10000, 10000};
    unsigned int maxPlants = 3000;

    void updateSpontaneousPlantSpawning(float deltaSeconds);
    void spontaneouslySpawnPlant();
    //Just prevents ecosystem dying once all the plants are gone
    int plantNumBelowWhichToSpontaneousSpawn = 200;
    float plantSpontaneousSpawnRate = 2.0f;
    float timeSinceSpontaneousPlantSpawn = 0.0f;

    World(); // Prevent construction
    World(const World&){}; // Prevent construction by copying
    World& operator=(const World&){return *this;}; // Prevent assignment
    ~World() = default; // Prevent unwanted destruction
};


#endif //EVOWORLD_WORLD_H

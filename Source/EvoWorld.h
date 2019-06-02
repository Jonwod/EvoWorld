//
// Created by jon on 25/05/19.
//

#ifndef EVOWORLD_EVOWORLD_H
#define EVOWORLD_EVOWORLD_H

#include <vector>
#include "Plant.h"
#include "Snake.h"


class EvoWorld {
public:
    EvoWorld();
    void update(float deltaSeconds);
    void draw(sf::RenderWindow & renderWindow) const;

    // Testing
    Vec2 getTestSnakePosition() const;
    //

private:
    void checkSnakeOnSnakeOverlaps();
    void reproduce(int snakeIndex);
    std::vector<Snake> _snakes;
    std::vector<Plant> _plants;
};


#endif //EVOWORLD_EVOWORLD_H

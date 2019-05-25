//
// Created by jon on 25/05/19.
//

#include "EvoWorld.h"
#include "Circle.h"


EvoWorld::EvoWorld() {
   _plants = std::vector<Plant>{Vec2{200.f, 200.f}, Vec2{300.f, 200.f}, Vec2{400.f, 300.f}};
   _snakes.push_back(Vec2{100.f, 100.f});
}


void EvoWorld::update(float deltaSeconds) {
    // ~~~~~~~~~~~Test controls~~~~~~~~~~~~~~
    Snake & snickers = _snakes[0];

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        snickers.setTargetAngle(-pi/2.f);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        snickers.setTargetAngle(0.f);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        snickers.setTargetAngle(pi / 2.f);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        snickers.setTargetAngle(pi);
    }
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    for(Snake & snake: _snakes){
        snake.update(deltaSeconds);
        for(Plant & plant: _plants){
            if(plant.isAlive()  &&  snake.doesHeadOverlap(plant.getCircle())){
                snake.eat(plant);
            }

        }
    }
}


void EvoWorld::draw(sf::RenderWindow &renderWindow) const {
    for(const Snake & snake: _snakes){
        snake.draw(renderWindow);
    }

    for(const Plant & plant: _plants){
        if(plant.isAlive())
            plant.draw(renderWindow);
    }
}

//
// Created by jon on 25/05/19.
//

#include "EvoWorld.h"
#include "Circle.h"
#include <iostream>


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
        if(snake.isAlive()) {
            snake.update(deltaSeconds);

            for (Plant &plant: _plants) {
                if (plant.isAlive() && snake.doesHeadOverlap(plant.getCircle())) {
                    snake.eat(plant);
                }

            }

            if(snake.wantsToReproduce()  &&  snake.canReproduce()){
                reproduce(snake);
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


void EvoWorld::reproduce(Snake & parentSnake) {
    constexpr int childSnakeSize = 3;

    if(parentSnake.numSegments() <= childSnakeSize){
        std::cout<<"Error in "<<__func__<<" parent snake of size "<<parentSnake.numSegments()<<
        " cannot spawn child""of size "<<childSnakeSize<<std::endl;
    }

    std::vector<Vec2> newSnakeSegs;
    for(int i = parentSnake.numSegments() - 1; i > parentSnake.numSegments() - childSnakeSize -1; --i){
        newSnakeSegs.push_back(parentSnake.getSegment(i));
    }

    _snakes.emplace_back(Snake(newSnakeSegs, parentSnake.getSegmentRadius()));
    parentSnake.removeSegments(3);
}

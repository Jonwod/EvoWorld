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

            checkSnakeOnSnakeOverlaps();
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
    constexpr int childSnakeSize = 2;

    if(parentSnake.numSegments() <= childSnakeSize){
        std::cout<<"Error in "<<__func__<<" parent snake of size "<<parentSnake.numSegments()<<
        " cannot spawn child""of size "<<childSnakeSize<<std::endl;
    }

    std::vector<Vec2> newSnakeSegs;
    const int finalParentSegment = parentSnake.numSegments() - childSnakeSize;
    for(int i = parentSnake.numSegments() - 1; i >= finalParentSegment;  --i){
        newSnakeSegs.push_back(parentSnake.getSegment(i));
    }

    _snakes.emplace_back(Snake(newSnakeSegs, parentSnake.getSegmentRadius()));
    parentSnake.removeSegments(childSnakeSize);
}


void EvoWorld::checkSnakeOnSnakeOverlaps() {
    for(int i = 0; i < _snakes.size(); ++i){
        for(int j = i + 1; j < _snakes.size(); ++j){

            if(_snakes[i].doesHeadOverlap(Circle(_snakes[j].getSegment(0), _snakes[i].getSegmentRadius()))){
                // Heads overlap. Smallest snake dies
                if(_snakes[i].numSegments() == _snakes[j].numSegments()){
                    _snakes[i].die();
                    _snakes[j].die();
                }
                else if(_snakes[i].numSegments() > _snakes[j].numSegments()){
                    _snakes[j].die();
                }
                else{
                    _snakes[i].die();
                }
            }
            else if(_snakes[i].doesHeadOverlapOtherSnakeTail(_snakes[j])){
                _snakes[i].die();
            }
            else if(_snakes[j].doesHeadOverlapOtherSnakeTail(_snakes[i])){
                _snakes[j].die();
            }
        }
    }
}

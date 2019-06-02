//
// Created by jon on 25/05/19.
//

#include "EvoWorld.h"
#include "Circle.h"
#include <iostream>


EvoWorld::EvoWorld() {
   _plants = std::vector<Plant>{Vec2{200.f, 200.f}, Vec2{300.f, 200.f}, Vec2{400.f, 300.f}};

   _snakes.push_back(Vec2{500.f, 200.f});

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

    snickers.setBoosting(sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    for(int i = 0; i < _snakes.size(); ++i){
        if(_snakes[i].isAlive()) {
            _snakes[i].update(deltaSeconds);

            for (Plant &plant: _plants) {
                if (plant.isAlive() && _snakes[i].doesHeadOverlap(plant.getCircle())) {
                    _snakes[i].eat(plant);
                }

            }

            if(_snakes[i].wantsToReproduce()  &&  _snakes[i].canReproduce()){
                reproduce(i);
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


void EvoWorld::reproduce(int parentSnakeIndex) {
    if(parentSnakeIndex < 0  ||  parentSnakeIndex >= _snakes.size()){
        std::cout<<"ERROR in "<<__func__<<": invalid snake index "<<parentSnakeIndex<<". _snakes.size() is "
        <<_snakes.size()<<std::endl;
    }

    constexpr int childSnakeSize = 2;

    if(_snakes[parentSnakeIndex].numSegments() <= childSnakeSize){
        std::cout<<"Error in "<<__func__<<" parent snake of size "<<_snakes[parentSnakeIndex].numSegments()<<
        " cannot spawn child""of size "<<childSnakeSize<<std::endl;
    }

    std::vector<Vec2> newSnakeSegs;
    const int finalParentSegment = _snakes[parentSnakeIndex].numSegments() - childSnakeSize;
    for(int i = _snakes[parentSnakeIndex].numSegments() - 1; i >= finalParentSegment;  --i){
        newSnakeSegs.push_back(_snakes[parentSnakeIndex].getSegment(i));
    }

    const float childSnakeAngle = angleOf(newSnakeSegs[0] - newSnakeSegs[1]);
    _snakes.emplace_back(newSnakeSegs, _snakes[parentSnakeIndex].getSegmentRadius(), childSnakeAngle);
    _snakes[parentSnakeIndex].removeSegments(childSnakeSize);
}


void EvoWorld::checkSnakeOnSnakeOverlaps() {
    for(int i = 0; i < _snakes.size(); ++i){
        for(int j = i + 1; j < _snakes.size(); ++j){
            if(_snakes[i].isAlive()  &&  _snakes[j].isAlive()) {
                if (_snakes[i].doesHeadOverlap(Circle(_snakes[j].getSegment(0), _snakes[i].getSegmentRadius()))) {
                    // Heads overlap. Smallest snake dies
                    if (_snakes[i].numSegments() == _snakes[j].numSegments()) {
                        _snakes[i].die();
                        _snakes[j].die();
                    } else if (_snakes[i].numSegments() > _snakes[j].numSegments()) {
                        _snakes[j].die();
                    } else {
                        _snakes[i].die();
                    }
                } else if (_snakes[i].doesHeadOverlapOtherSnakeTail(_snakes[j])) {
                    _snakes[i].die();
                } else if (_snakes[j].doesHeadOverlapOtherSnakeTail(_snakes[i])) {
                    _snakes[j].die();
                }
            }
        }
    }
}


Vec2 EvoWorld::getTestSnakePosition() const {
    return _snakes.empty() ? Vec2(0, 0) : _snakes[0].getSegment(0);
}

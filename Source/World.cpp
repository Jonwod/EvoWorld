//
// Created by jon on 25/05/19.
//

#include "World.h"
#include "Circle.h"
#include <iostream>


World::World() {
   _snakes.emplace_back(std::vector<Vec2>{Vec2{200, 200}}, 25.f);
   _snakes[0].addSegment();
   _snakes[0].addSegment();
}


void World::update(float deltaSeconds) {
    // ~~~~~~~~~~~Test controls~~~~~~~~~~~~~~
//    Snake & snickers = _snakes[0];
//
//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
//        snickers.setTargetAngle(-pi/2.f);
//    }
//    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
//        snickers.setTargetAngle(0.f);
//    }
//    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
//        snickers.setTargetAngle(pi / 2.f);
//    }
//    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
//        snickers.setTargetAngle(pi);
//    }
//
//    snickers.setBoosting(sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    clearDead();

    updateSpontaneousPlantSpawning(deltaSeconds);

    for(int i = 0; i < _snakes.size(); ++i){
        if(_snakes[i].isAlive()) {
            _snakes[i].update(deltaSeconds);

            if(_snakes[i].wantsToReproduce()  &&  _snakes[i].canReproduce()){
                reproduce(i);
            }

            for (Plant &plant: _plants) {
                if (plant.isAlive() && _snakes[i].doesHeadOverlap(plant.getCircle())) {
                    _snakes[i].eat(plant);
                }

            }

            for(Meat& meat: _meat){
                if(_snakes[i].doesHeadOverlap(Circle(meat.getPosition(), meat.getRadius())))
                    _snakes[i].eat(meat);
            }
        }
    }

    checkSnakeOnSnakeOverlaps();

    for(Plant & plant: _plants){
        if(plant.isAlive()){
            plant.update(deltaSeconds);
        }
    }
}


void World::draw(sf::RenderWindow &renderWindow) const {
    for(const Plant & plant: _plants){
        if(plant.isAlive())
            plant.draw(renderWindow);
    }

    for(const Meat& meat: _meat){
        if(!meat.isDestroyed())
         meat.draw(renderWindow);
    }

    for(const Snake & snake: _snakes){
        snake.draw(renderWindow);
    }
}


void World::reproduce(int parentSnakeIndex) {
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


void World::checkSnakeOnSnakeOverlaps() {
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


Vec2 World::getTestSnakePosition() const {
    return _snakes.empty() ? Vec2(0, 0) : _snakes[0].getSegment(0);
}


void World::updateSpontaneousPlantSpawning(float deltaSeconds){
    if(_plants.size() < plantNumBelowWhichToSpontaneousSpawn  &&  timeSinceSpontaneousPlantSpawn >= 1.0f / plantSpontaneousSpawnRate){
        spontaneouslySpawnPlant();
        timeSinceSpontaneousPlantSpawn = 0.0f;
    }
    timeSinceSpontaneousPlantSpawn += deltaSeconds;
}


void World::spawnPlant(const Plant &plantTemplate) {
    if(_plants.size() < maxPlants  &&  inhabitableZone.contains(plantTemplate.getPosition())){
        _plants.push_back(plantTemplate);
    }
}


void World::spontaneouslySpawnPlant() {
    float randX = randFloat(inhabitableZone.left, inhabitableZone.left + inhabitableZone.width);
    float randY = randFloat(inhabitableZone.top, inhabitableZone.top + inhabitableZone.height);
    Plant plantTemplate{};
    plantTemplate.setPosition({randX, randY});
    spawnPlant(plantTemplate);
}


void World::spawnMeat(const std::vector<Vec2> &meatPositions, float meatRadius, sf::Color color) {
    for(const Vec2& pos: meatPositions) {
        _meat.emplace_back(pos, meatRadius, color);
    }
}


void World::clearDead() {
    for(int i = _plants.size() - 1; i >= 0; --i){
        if(!_plants[i].isAlive())
            _plants.erase(_plants.begin() + i);
    }

    for(int i = _snakes.size() - 1; i >= 0; --i){
        if(!_snakes[i].isAlive())
            _snakes.erase(_snakes.begin() + i);
    }

    for(int i = _meat.size() - 1; i >= 0; --i){
        if(_meat[i].isDestroyed())
            _meat.erase(_meat.begin() + i);
    }
}

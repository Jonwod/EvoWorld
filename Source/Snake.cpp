//
// Created by jon on 12/05/19.
//

#include "Snake.h"
#include "World.h"
#include <vector>
#include <utility>
#include <iostream>


Snake::Snake(std::vector<Vec2> initSegments, float radius, float initAngle)
    :_segments(std::move(initSegments)),
    _segmentRadius(radius),
    _angle(initAngle)
{
    // ...
}


void Snake::draw(sf::RenderWindow &renderWindow) const {
    if(!_segments.empty()) {
        sf::CircleShape circle{getSegmentRadius()};
        circle.setOrigin(circle.getRadius(), circle.getRadius());
        circle.setFillColor(_color);
        circle.setOutlineThickness(1.f);

        for (int i = _segments.size() - 1; i >= 0; --i) {
            circle.setPosition(_segments[i]);
            renderWindow.draw(circle);
        }

        _drawEyes(renderWindow);
    }
}


bool Snake::addSegment() {
    if(!_segments.empty()){
        _segments.push_back(_segments.back() - unitVector(_angle) * _segmentSpacing());
        return true;
    }

    return false;
}


void Snake::_drawEyes(sf::RenderWindow &renderWindow) const {
    sf::CircleShape circle{getSegmentRadius() * 0.2f};
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setFillColor(sf::Color::White);

    const Vec2 eyeCentre = _segments[0] + unitVector(_angle) * getSegmentRadius() * 0.3f;
    const float eyeDistance = getSegmentRadius() * 0.4f;
    circle.setPosition(eyeCentre + unitVector(_angle + pi * 0.5f) * eyeDistance);
    renderWindow.draw(circle);
    circle.setPosition(eyeCentre - unitVector(_angle + pi * 0.5f) * eyeDistance);
    renderWindow.draw(circle);
}


void Snake::update(float dt) {
    _angle += _brain.getOutput().steer * _turnSpeed * dt;

    if(!_segments.empty()) {
        _segments[0] += unitVector(_angle) * getCurrentSpeed() * dt;
    }

    for(int i = 1; i < _segments.size(); ++i){
        const Vec2 offsetFromParent = _segments[i] - _segments[i - 1];
        const Vec2 targetOffset = normal(offsetFromParent) * _segmentSpacing();
        _segments[i] = _segments[i - 1] + targetOffset;
    }

    if(isBoosting()){
        _energy -= _getBoostEnergyUseRate() * dt;
    }
}


float Snake::_segmentSpacing() const {
    return getSegmentRadius() * 1.5f;
}


void Snake::eat(Plant &plant) {
    _grantEnergy(plant.consume());
}


void Snake::eat(Meat& meat) {
    _grantEnergy(meat.consume());
}


void Snake::_grantEnergy(float newEnergy) {
    _energy += newEnergy;
    while(_energy > _getEnergyNeededToGrow()){
        grow();
    }
}


bool Snake::doesHeadOverlap(const Circle &queryCircle) const {
    if(!_segments.empty()){
        Circle headCircle{_segments[0], _segmentRadius};
        return headCircle.overlaps(queryCircle);
    }
    return false;
}


float Snake::_getEnergyNeededToGrow() const{
    return _segmentRadius * 2.1f;
}


void Snake::grow() {
    _energy -= _getEnergyNeededToGrow();
    addSegment();
}


void Snake::removeSegments(int16_t numberOfSegments) {
    if (numberOfSegments > _segments.size()) {
        std::cout<<"ERROR in "<<__func__<<": trying to remove "<<numberOfSegments<<" segments from snake with "<<
        _segments.size()<<" segments"<<std::endl;
        return;
    }

    for(int i = 0; i < numberOfSegments; ++i){
        _segments.pop_back();
    }
}


bool Snake::doesHeadOverlapOtherSnakeTail(const Snake &otherSnake) const{
    for(int i = 1; i < otherSnake.numSegments(); ++i){
        if(doesHeadOverlap(Circle(otherSnake.getSegment(i), otherSnake.getSegmentRadius()))){
            return true;
        }
    }
    return false;
}


void Snake::die() {
    World::get().spawnMeat(_segments, _segmentRadius, _color);
    _segments.clear();
    std::cout<<"He ded"<<std::endl;
}


float Snake::getCurrentSpeed() const {
    return isBoosting() ? _boostSpeed : _baseSpeed;
}


float Snake::_getBoostEnergyUseRate() const {
    return _segmentRadius / 5.f;
}


bool Snake::isBoosting() const {
    return _brain.getOutput().boost  &&  _energy > 0.f;
}

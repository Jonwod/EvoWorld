#include <utility>

//
// Created by jon on 12/05/19.
//

#include "Snake.h"
#include <vector>
#include <iostream>


Snake::Snake(const Vec2& initPosition)
{
    // Create head
    _segments.push_back(initPosition);

    constexpr int initSegments{3};
    for(int i = 1 ; i < initSegments; ++i){
        addSegment();
    }
}


Snake::Snake(std::vector<Vec2> initSegments, float radius, float initAngle)
    :_segmentRadius(radius),
    _angle(initAngle),
    _targetAngle(initAngle)
{
    _segments = initSegments;
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
    _updateAngle(dt);

    if(!_segments.empty()) {
        _segments[0] += unitVector(_angle) * getCurrentSpeed() * dt;
    }

    for(int i = 1; i < _segments.size(); ++i){
        const Vec2 offsetFromParent = _segments[i] - _segments[i - 1];
        const Vec2 targetOffset = normal(offsetFromParent) * _segmentSpacing();
        _segments[i] = _segments[i - 1] + targetOffset;
    }
}


float Snake::_segmentSpacing() const {
    return getSegmentRadius() * 1.5f;
}


void Snake::_updateAngle(float dt) {
    if(!nearlyEqual(_angle, _targetAngle, 0.0001f)){
        const float targetOffset = normalizeAngle(_targetAngle - _angle);
        const float deltaAngle = _angularSpeed * dt * (targetOffset / fabsf(targetOffset));

        if(fabsf(deltaAngle) > fabsf(targetOffset)){
            _angle = _targetAngle;
        }
        else{
            _angle += deltaAngle;
        }
    }
}


void Snake::eat(Plant &plant) {
    _grantEnergy(plant.consume());
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
    return _segmentRadius;
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

    std::cout<<"Removing segments. Start with: "<<_segments.size();

    for(int i = 0; i < numberOfSegments; ++i){
        _segments.pop_back();
    }
    std::cout<<" End with: "<<_segments.size()<<std::endl;
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
    _segments.clear();
    std::cout<<"He ded"<<std::endl;
}


void Snake::setBoosting(bool shouldBoost) {
    _isBoosting = shouldBoost;
}


float Snake::getCurrentSpeed() const {
    return _isBoosting ? _boostSpeed : _baseSpeed;
}

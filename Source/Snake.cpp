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

        drawEyes(renderWindow);
    }
}


bool Snake::addSegment() {
    if(!_segments.empty()){
        _segments.push_back(_segments.back() - unitVector(_angle) * segmentSpacing());
        return true;
    }

    return false;
}


void Snake::drawEyes(sf::RenderWindow &renderWindow) const {
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
    updateAngle(dt);

    if(!_segments.empty()) {
        _segments[0] += unitVector(_angle) * _baseSpeed * dt;
    }

    for(int i = 1; i < _segments.size(); ++i){
        const Vec2 offsetFromParent = _segments[i] - _segments[i - 1];
        const Vec2 targetOffset = normal(offsetFromParent) * segmentSpacing();
        _segments[i] = _segments[i - 1] + targetOffset;
    }
}


float Snake::segmentSpacing() const {
    return getSegmentRadius() * 1.5f;
}


void Snake::updateAngle(float dt) {
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

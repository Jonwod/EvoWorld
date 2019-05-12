//
// Created by jon on 12/05/19.
//

#include "Snake.h"
#include <vector>


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
    if(_segments.size()) {
        sf::CircleShape circle{getSegmentRadius()};
        circle.setOrigin(circle.getRadius(), circle.getRadius());
        circle.setFillColor(_color);

        for (const Vec2 &segment:_segments) {
            circle.setPosition(segment);
            renderWindow.draw(circle);
        }

        drawEyes(renderWindow);
    }
}


bool Snake::addSegment() {
    if(_segments.size()){
        _segments.push_back(_segments.back() - unitVector(_angle) * getSegmentRadius() * 1.5f);
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

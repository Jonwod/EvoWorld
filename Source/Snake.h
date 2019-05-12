//
// Created by jon on 12/05/19.
//

#ifndef EVOWORLD_SNAKE_H
#define EVOWORLD_SNAKE_H
#include <vector>
#include "Math.h"
#include "SFML/Graphics.hpp"


class Snake {
public:
    Snake(const Vec2& initPosition);

    void update(float dt);

    void draw(sf::RenderWindow & renderWindow) const;

    inline float getSegmentRadius() const { return _segmentRadius;};

    bool addSegment();

    inline void setTargetAngle(float newAng){_targetAngle = newAng;}
private:
    void drawEyes(sf::RenderWindow & renderWindow) const;

    float segmentSpacing() const;

    void updateAngle(float dt);

     // _segments[0] is the head
    std::vector<Vec2> _segments;

    /* In radians */
    float _angle = 0.f;
    float _targetAngle = 0.f;
    static constexpr float _angularSpeed = pi;

    static constexpr float _segmentRadius{25.f};

    static constexpr float _baseSpeed = 50.f;

    sf::Color _color{125, 125, 0};
};


#endif //EVOWORLD_SNAKE_H

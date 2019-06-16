//
// Created by jon on 12/05/19.
//

#ifndef EVOWORLD_SNAKE_H
#define EVOWORLD_SNAKE_H
#include <vector>
#include "Math.h"
#include "Plant.h"
#include "Circle.h"
#include "Meat.h"
#include "Brain.h"
#include "SFML/Graphics.hpp"


class Snake {
public:
    // First element is head
    Snake(std::vector<Vec2> initSegments, float radius, float initAngle = 0.f);

    void update(float dt);

    void draw(sf::RenderWindow & renderWindow) const;

    inline float getSegmentRadius() const { return _segmentRadius;};

    bool addSegment();

    inline void setTargetAngle(float newAng){_targetAngle = newAng;}

    bool doesHeadOverlap(const Circle & queryCircle) const;

    bool doesHeadOverlapOtherSnakeTail(const Snake & otherSnake) const;

    void eat(Plant & plant);

    void eat(Meat & meat);

    bool isAlive() const { return !_segments.empty(); };

    bool wantsToReproduce() const { return _wantsToReproduce;};

    bool canReproduce() const { return _segments.size() > 3; };

    void removeSegments(int16_t numberOfSegments);

    std::size_t numSegments() const { return _segments.size(); };

    // Where 0 is the head and numSegments() - 1 is the last segment
    const Vec2& getSegment(std::size_t segmentIndex) const { return _segments[segmentIndex]; };

    void die();

    void setBoosting(bool shouldBoost);

    // Returns the current (scalar) speed
    float getCurrentSpeed() const;
private:
    void _drawEyes(sf::RenderWindow &renderWindow) const;
    float _segmentSpacing() const;
    void _updateAngle(float dt);
    void _grantEnergy(float newEnergy);
    float _getEnergyNeededToGrow() const;
    void grow();
    float _getBoostEnergyUseRate() const;

     // _segments[0] is the head
    std::vector<Vec2> _segments;

    /* In radians */
    float _angle = 0.f;
    float _targetAngle = 0.f;
    static constexpr float _angularSpeed = pi;

    float _segmentRadius{25.f};

    static constexpr float _baseSpeed = 50.f;

    static constexpr float _boostSpeed = 100.f;

    bool _isBoosting = false;

    sf::Color _color{125, 25, 50};

    float _energy = 0.f;

    bool _wantsToReproduce = true;


    /* Brain inputs:
        0: delta time
     */
    static constexpr size_t brainInputs = 1;

    /* Brain outputs:
        0: direction x
        1: direction y
        2: boost
        3: reproduce
    */
    static constexpr size_t brainOutputs = 4;
    Brain<brainInputs, brainOutputs> _brain;

    void _processBrainOutput(const std::array<float, brainOutputs> brainOut);
};


#endif //EVOWORLD_SNAKE_H

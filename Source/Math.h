//
// Created by jon on 04/05/19.
//

#ifndef EVOWORLD_MATH_H
#define EVOWORLD_MATH_H

#include <SFML/System.hpp>
#include <string>
#include <cmath>

typedef sf::Vector2f Vec2;

Vec2 unitVector(float angleInRadians);

std::string str(const Vec2 & vec);

inline float len(const Vec2 vec) {
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

constexpr float pi = 3.14159265358979323846f;



#endif //EVOWORLD_MATH_H

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

inline float angleOf(const Vec2& vector){
    return atan2(vector.y, vector.x);
}

Vec2 normal(const Vec2& vec);

std::string str(const Vec2 & vec);


inline float len(const Vec2 vec) {
    return sqrtf(vec.x * vec.x + vec.y * vec.y);
}


constexpr float pi = 3.14159265358979323846f;


inline float normalizeAngle(float angleRadians){
    float x = fmodf(angleRadians + pi, 2 * pi);
    if(x < 0)
        x += 2 * pi;
    return x - pi;
}


inline bool nearlyEqual(float a, float b, float tolerance){
    return fabsf(a - b) < tolerance;
}

int randInt(int n1, int n2);

float randFloatClamped();

float randFloat(float n1, float n2);


#endif //EVOWORLD_MATH_H

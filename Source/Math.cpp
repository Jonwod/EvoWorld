//
// Created by jon on 04/05/19.
//

#include "Math.h"
#include <cmath>

Vec2 unitVector(float angleInRadians) {
    return Vec2(cosf(angleInRadians), sinf(angleInRadians));
}


std::string str(const Vec2 &vec) {
    return std::string{"(" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ")"};
}


Vec2 normal(const Vec2 &vec) {
    const float length = len(vec);
    return length > 0.f ? vec / length : Vec2(0.f, 0.f);
}


int randInt(int n1, int n2){
    return  rand() % (n2-n1) +n1;
}

float randFloatClamped(){
    float rndfltcmp = float(randInt(0, 100000) / 100000.0f);
    return rndfltcmp;
}

float randFloat(float n1, float n2){
    return randFloatClamped() * (n2 - n1) + n1;
}
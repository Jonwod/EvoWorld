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

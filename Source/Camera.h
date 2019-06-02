//
// Created by jon on 02/06/19.
//

#ifndef EVOWORLD_CAMERA_H
#define EVOWORLD_CAMERA_H

#include<SFML/Graphics.hpp>
#include "Math.h"

void updateCamera(float dt, sf::View & view, sf::RenderWindow & window, const Vec2& position);

#endif //EVOWORLD_CAMERA_H

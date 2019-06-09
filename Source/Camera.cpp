//
// Created by jon on 02/06/19.
//

#include "Camera.h"


void updateCamera(float dt, sf::View & view, sf::RenderWindow & window, const Vec2& position){
    const static float scrollRate = 200.0f;
    const static float zoomRate = 0.2f;
    const float zoom = view.getSize().x / window.getSize().x;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        view.move(0, -scrollRate*zoom*dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        view.move(0, scrollRate*zoom*dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        view.move(scrollRate*zoom*dt, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        view.move(-scrollRate*zoom*dt, 0);

   // view.setCenter(position);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        view.zoom((1-zoomRate*dt));
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        view.zoom(1+zoomRate*dt);

    window.setView(view);
}
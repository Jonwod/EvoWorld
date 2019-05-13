#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Snake.h"
#include "Math.h"

#include <cfenv>

//bool testCircleBody(){
//    CircleBody circle1{10.f, {0.f, 0.f}};
//    CircleBody circle2{5.f, {-10.f, 13}};
//    return !circle1.overlaps(circle2);
//}


int main()
{
    feenableexcept(FE_INVALID | FE_OVERFLOW);


    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    window.setFramerateLimit(60);

    Snake snickers{Vec2(100.f, 100.f)};
    snickers.setTargetAngle(pi/2);

    constexpr float dt = 1.f / 60.f;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            snickers.setTargetAngle(-pi/2.f);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            snickers.setTargetAngle(0.f);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            snickers.setTargetAngle(pi / 2.f);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            snickers.setTargetAngle(pi);
        }


        window.clear();

        // ~~~~Draw~~~~~
        snickers.update(dt);
        snickers.draw(window);
        // ~~~~~~~~~~~~~

        window.display();
    }

    return 0;
}

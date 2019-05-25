#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Math.h"
#include "Snake.h"
#include "Plant.h"
#include "EvoWorld.h"

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

    EvoWorld world;

    constexpr float dt = 1.f / 60.f;
    while (window.isOpen())
    {
        // ~~~~~~~~~~~Event Handling~~~~~~~~~~~
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ~~~~Update/Draw~~~~~
        world.update(dt);
        window.clear();
        world.draw(window);
        // ~~~~~~~~~~~~~

        window.display();
    }

    return 0;
}

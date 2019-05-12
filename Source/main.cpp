#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Snake.h"
#include "Math.h"

//bool testCircleBody(){
//    CircleBody circle1{10.f, {0.f, 0.f}};
//    CircleBody circle2{5.f, {-10.f, 13}};
//    return !circle1.overlaps(circle2);
//}


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

    Snake snickers{Vec2(100.f, 100.f)};

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // ~~~~Draw~~~~~
        snickers.draw(window);
        // ~~~~~~~~~~~~~

        window.display();
    }

    return 0;
}

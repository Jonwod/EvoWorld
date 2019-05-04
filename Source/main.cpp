#include <SFML/Graphics.hpp>
#include <iostream>
#include "CircleBody.h"
#include "CircleBodyPart.h"

bool testCircleBody(){
    CircleBody circle1{10.f, {0.f, 0.f}};
    CircleBody circle2{5.f, {-10.f, 13}};
    return !circle1.overlaps(circle2);
}


int main()
{
    CircleBodyPart bodyPart(50.f);

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        bodyPart.draw(window);
        window.display();
    }

    return 0;
}

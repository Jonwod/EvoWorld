#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Math.h"
#include "Snake.h"
#include "Plant.h"
#include "World.h"
#include "Camera.h"

#include <cfenv>

//bool testCircleBody(){
//    CircleBody circle1{10.f, {0.f, 0.f}};
//    CircleBody circle2{5.f, {-10.f, 13}};
//    return !circle1.overlaps(circle2);
//}


//bool testAngleOf(float testAngle){
//    Vec2 testVec = unitVector(testAngle);
//    std::cout<<"unitVector("<<testAngle<<") = "<<str(testVec);
//    std::cout<<" angleOf("<<str(testVec)<<") = "<<angleOf(testVec)<<std::endl;
//    return testAngle == angleOf(testVec);
//}


int main()
{
    feenableexcept(FE_INVALID | FE_OVERFLOW);

    constexpr int window_x = 800;
    constexpr int window_y = 600;

    sf::RenderWindow window(sf::VideoMode(window_x, window_y), "SFML works!");
    window.setFramerateLimit(60);

    sf::View view;
    view.reset(sf::FloatRect(0, 0, window_x, window_y));
    view.setViewport(sf::FloatRect(0,0 ,1.0f, 1.0f));

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

        updateCamera(dt, view, window, World::get().getTestSnakePosition());

        // ~~~~Update/Draw~~~~~
        World::get().update(dt);
        window.clear();
        World::get().draw(window);
        // ~~~~~~~~~~~~~

        window.display();
    }

    return 0;
}

#include "CircleBodyPart.h"


CircleBodyPart::CircleBodyPart(float radius)
    :_physBody(radius)
{
    //ctor
}


void CircleBodyPart::draw(sf::RenderWindow & renderWindow) const{
    renderWindow.draw(sf::CircleShape(_physBody.getRadius()));
}

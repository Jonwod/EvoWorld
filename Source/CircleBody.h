#ifndef CIRCLEBODY_H
#define CIRCLEBODY_H
#include "SFML/System/Vector2.hpp"


class CircleBody{
    public:
        CircleBody(float radius, sf::Vector2f initPosition = sf::Vector2f(0.f, 0.f));

        inline float getRadius() const { return _radius; }
        inline void setRadius(float radius) { _radius = radius;}

        inline sf::Vector2f getPosition() const {return _position;}
        inline void setPosition(const sf::Vector2f position) { _position = position;}

        inline bool overlaps(const CircleBody & other) const {
            const sf::Vector2f diff = other.getPosition() - getPosition();
            const float sumOfRadii = getRadius() + other.getRadius();
            return (diff.x * diff.x + diff.y * diff.y) <= (sumOfRadii * sumOfRadii);
        }

    private:
        float _radius = 0.f;
        sf::Vector2f _position;
};

#endif // CIRCLEBODY_H

#pragma once
#include <SFML/Graphics.hpp>

class food
{
    public:
        food();
        virtual ~food();
        void draw(sf::RenderWindow& window);
    protected:

    private:
        sf::CircleShape shape;

};

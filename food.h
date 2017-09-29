#pragma once
#include "utils.h"
#include<iostream>
#include <SFML/Graphics.hpp>



class food
{
    public:
        food();
        virtual ~food();
        void setPosition(int x, int y);
        std::vector<float> getPosition();
        void draw(sf::RenderWindow& window);
    protected:

    private:
        sf::CircleShape shape;

};

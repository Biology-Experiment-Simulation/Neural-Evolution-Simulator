#pragma once
#include <SFML/Graphics.hpp>
#include "neuralNet/Net.h"

class animal
{
    public:
        animal();
        virtual ~animal();
        void draw(sf::RenderWindow& window);
        void crossover(animal& matingPartner);
        void mutate();
        void resetBrain();

    protected:

    private:
         NN::Net brain;
        sf::CircleShape shape;
        int fitnessScore = 0;
};

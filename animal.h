#pragma once
#include "utils.h"
#include<iostream>
#include <SFML/Graphics.hpp>
#include "neuralNet/Net.h"



class animal
{
    public:
        animal();
        virtual ~animal();

        void runAnimal(std::vector<int> input);
        void setPosition(int x, int y);
        std::vector<int> getPosition();
        void draw(sf::RenderWindow& window);
        void crossover(animal& matingPartner);
        void mutate();
        void resetBrain();
        void resetFitnessScore();

    protected:

    private:
        NN::Net brain;
        sf::CircleShape shape;
        int fitnessScore = 0;
};

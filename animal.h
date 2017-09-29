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

        NN::Net brain;
        int fitnessScore = 0;
        unsigned closestFood = 0;

        void runAnimal(std::vector<float>& input);
        void setPosition(int x, int y);
        std::vector<float> getPosition();
        void draw(sf::RenderWindow& window);
        void crossover(animal& matingPartner);
        void mutate();
        void setNewBrainWeights(std::vector<float>& newWeights);
        void resetBrain();
        void resetFitnessScore();

    protected:

    private:
        sf::CircleShape shape;
};

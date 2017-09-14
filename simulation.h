#pragma once
#include "neuralNet/Net.h"
#include <SFML/Graphics.hpp>

/// .......... Random functions Data .............. //////////////
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_real_distribution<float> randomVal(-3.2, 3.4);
    static std::uniform_int_distribution<int> uniform_dist(0, 42);

    static float rands(float a, float b)
    {
    return ((b-a)*((float)rand()/RAND_MAX))+a;
    }


class Simulation{
private:
    int animalCount = 10;
    int simulationTime = 1500;

public:
    std::vector<NN::Net> brains;
    std::vector<float> input, output;
    sf::CircleShape animal[10],food[10];
    std::vector<float> bestWeights, secondbestWeights;
    int firstBest = 0; int secondBest = 0;

    Simulation();
    ~Simulation();

    static float distance(float x1, float x2, float y1, float y2);

    void setNetTopology(unsigned inputSize, unsigned hiddenLayerSize, unsigned hiddenLayers, unsigned outputSize);
    void createAnimals();
    void createFood();
    void runSimulation(sf::RenderWindow& window);
    void setClosestFood(int creatureId);
    void setTwoBestAnimals();
    void evolve();
    void proccessCreatures();




};


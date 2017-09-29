#pragma once
#include <memory>
#include "utils.h"
#include "animal.h"
#include "food.h"
#include "neuralNet/Net.h"
#include <SFML/Graphics.hpp>

/// .......... Random functions Data .............. //////////////
    static std::uniform_real_distribution<float> randomVal(-3.2, 3.4);
    static std::uniform_real_distribution<float> randomInput(-0.05, 0.05);
    static std::uniform_int_distribution<int> uniform_dist(0, 42);

    typedef std::shared_ptr<NN::Net> NetPtr;
    typedef std::shared_ptr<animal> animalPtr;
    typedef std::shared_ptr<food> foodPtr;


class Simulation{
private:
    int simulationTime = 1500;
    std::vector<float> input, output;
    std::vector<float> bestWeights, secondbestWeights;
    unsigned firstBest = 0; unsigned secondBest = 0;

    std::vector<animalPtr> animals;
    std::vector<foodPtr> foods;

    void setClosestFood(int creatureId);
    void setTwoBestAnimals();
    void evolve();
    void proccessCreatures();

public:


    Simulation();
    ~Simulation();

    static float distance(float x1, float x2, float y1, float y2);
    static float distance(std::vector<float> animalPos, std::vector<float> FoodPos);

    void setNetTopology(unsigned inputSize, unsigned hiddenLayerSize, unsigned hiddenLayers, unsigned outputSize);
    void createAnimals(int number);
    void createFood(int number);
    void runSimulation(sf::RenderWindow& window);


};


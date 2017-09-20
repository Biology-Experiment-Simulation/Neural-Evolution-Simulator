#pragma once
#include <memory>
#include "utils.h"
#include "animal.h"
#include "food.h"
#include "neuralNet/Net.h"
#include <SFML/Graphics.hpp>

/// .......... Random functions Data .............. //////////////
    static std::uniform_real_distribution<float> randomVal(-3.2, 3.4);
    static std::uniform_int_distribution<int> uniform_dist(0, 42);

    typedef std::shared_ptr<NN::Net> NetPtr;


class Simulation{
private:
    int animalCount = 10;
    int simulationTime = 1500;
    std::vector<float> input, output;
    sf::CircleShape animaly[10];
    sf::CircleShape foody[10];
    std::vector<float> bestWeights, secondbestWeights;
    int firstBest = 0; int secondBest = 0;

    std::vector<animal> animals;
    std::vector<food> foods;
    std::vector<NetPtr> brains;

    void setClosestFood(int creatureId);
    void setTwoBestAnimals();
    void evolve();
    void proccessCreatures();

public:


    Simulation();
    ~Simulation();

    static float distance(float x1, float x2, float y1, float y2);
    static float distance(std::vector<int> animalPos, std::vector<int> FoodPos);

    void setNetTopology(unsigned inputSize, unsigned hiddenLayerSize, unsigned hiddenLayers, unsigned outputSize);
    void createAnimals(int number);
    void createFood(int number);
    void runSimulation(sf::RenderWindow& window);


};


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include<iostream>
#include<vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include"neuralNet/Net.h"
#include"simulation.h"

int main()
{
    std::srand(static_cast<float>(std::time(NULL)));

    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Neural-Evolution balls");
    window.setVerticalSyncEnabled(true);

    Simulation sim;
    sim.createFood();
    sim.createAnimals();
    sim.runSimulation(window);

    return EXIT_SUCCESS;


}




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
    /// //////////////////// Brains  //////////////////////////// ////////////


    float xz,yz; /// FOOD POSITION
    sf::Clock AITimer;
    const sf::Time AITime   = sf::seconds(0.004f);
    bool foodSet = false;
    int simulationTime = 59 * 10;

    Simulation aa;
    aa.createFood();
    aa.createAnimals();
    sf::Clock clock;
    bool isPlaying = false;

    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Neural-Evolution balls");
    window.setVerticalSyncEnabled(true);
    while (window.isOpen())
    {
        if (!isPlaying)
                {
                        isPlaying = true;
                        for (int i=0;i<10;i++){
                            aa.food[i].setPosition(rands(0,800),rands(0,600));
                        }
                        for (int i=0;i<10;i++){
                           aa.animal[i].setPosition(rands(0,800),rands(0,600));
                           aa.setClosestFood(i);
                        }
                        clock.restart();
                }

        // Handle events
        sf::Event event;
        while ( window.pollEvent(event))
        {
            if ((event.type == sf::Event::Closed) ||
               ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
            {
                window.close();
                break;
            }
        }
        if (isPlaying)
        {
             if (AITimer.getElapsedTime() > AITime)
            {
                /// One Generation time
                simulationTime--;
                if(simulationTime ==0)
                   {
                       std::cout << "fitness scores" << std::endl;
                       int c =0; int scoreA=-4000;int scoreB=-4000;
                       for (auto& it : aa.brains){
                                std::cout << it.fitnessScore << std::endl;
                                  if(it.fitnessScore > scoreA){
                                        scoreA = it.fitnessScore;
                                        scoreB = scoreA;
                                        aa.secondBest = aa.firstBest;
                                        aa.firstBest = c;
                                   }else if(it.fitnessScore > scoreB){
                                       scoreB = it.fitnessScore;
                                       aa.secondBest = c;}
                                c++;
                       }
                       std::cout << "first best = " << aa.firstBest << "second best = " << aa.secondBest << std::endl;
                       aa.evolve();

                       for(int i=0;i<10;i++)
                       {
                           aa.animal[i].setPosition(rands(0,800),rands(0,600));
                           aa.brains[i].fitnessScore = 0;
                       }
                       aa.firstBest = 0; aa.secondBest = 0;simulationTime =1499;
                       isPlaying = false;foodSet=false;
                   }
                 if(simulationTime%500 == 0)
                   {
                      for (int i=0;i<10;i++){
                            aa.food[i].setPosition(rands(0,800),rands(0,600));
                        }
                        for (int i=0;i<10;i++){
                           aa.animal[i].setPosition(rands(444,600),rands(200,500));
                           aa.setClosestFood(i);
                        }
                    foodSet=false;
                 }
                AITimer.restart();
                aa.proccessCreatures();

            }
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
             {
                 foodSet=false;
             }
        }
       /// RENDER ALL /////////////////////////////////
        window.clear(sf::Color(20, 10, 250));
        for(int i=0;i<aa.brains.size();i++)
            {
                window.draw(aa.animal[i]);
                window.draw(aa.food[i]);
            }
        window.display();
    }

    return EXIT_SUCCESS;


}




#include "animal.h"

animal::animal() : brain(NN::Net(4,2,7,2))
{
    this->shape.setRadius(10 + 3);
    this->shape.setOutlineThickness(2);
    this->shape.setOutlineColor(sf::Color::Magenta);
    this->shape.setFillColor(sf::Color(255,55,0));
    this->shape.setOrigin(10 / 2, 10 / 2);
    this->shape.setPosition(rands(0,800),rands(0,600));
    std::cout << "default animal created with (4,2,7,2) brain!" << "\n";
}

animal::~animal()
{
   std::cout << "animal destroyed!" << "\n";
}

void animal::setPosition(int x, int y)
{
   this->shape.setPosition(x,y);
}

std::vector<int> animal::getPosition()
{
    std::vector<int> pos;
    pos.push_back(this->shape.getPosition().x);
    pos.push_back(this->shape.getPosition().y);
    return pos;
}

void animal::crossover(animal& matingPartner)
{
     std::vector<int> brainWeights, matingBrainWeights;
     brain.getWeights(brainWeights);
     matingPartner.getWeights(matingBrainWeights);


            std::uniform_int_distribution<int> uniform_dist(0, brainWeights.size());
            int crossover = uniform_dist(mt);

            for(int j=crossover;j< brainWeights.size() ;j++)
            {
                brainWeights[j] = matingBrainWeights[j];
            }
            brain.setWeights(brainWeights);

}

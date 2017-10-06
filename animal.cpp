#include "animal.h"

animal::animal() : brain(NN::Net(4,2,7,2))
{
    this->shape.setRadius(10 + 3);
    this->shape.setOutlineThickness(2);
    this->shape.setOutlineColor(sf::Color::Yellow);
    this->shape.setFillColor(sf::Color(255,55,0));
    this->shape.setOrigin(10 / 2, 10 / 2);
    this->shape.setPosition(rands(0,800),rands(0,600));
    std::cout << "default animal created with (4,2,7,2) brain!" << "\n";
}

animal::~animal()
{
   std::cout << "animal destroyed!" << "\n";
}

void animal::runAnimal(std::vector<float>& input)
{
    std::vector<float> output = brain.feedForward(input);
    this->shape.move(output[0]*4,output[1]*4);

}

void animal::setPosition(int x, int y)
{
   this->shape.setPosition(x,y);
}

std::vector<float> animal::getPosition()
{
    std::vector<float> pos;
    pos.push_back(this->shape.getPosition().x);
    pos.push_back(this->shape.getPosition().y);
    return pos;
}

void animal::crossover(animal& matingPartner)
{
     std::vector<float> brainWeights, matingBrainWeights;
     brain.getWeights(brainWeights);
     matingPartner.brain.getWeights(matingBrainWeights);


            std::uniform_int_distribution<int> uniform_dist(0, brainWeights.size());
            int crossover = uniform_dist(mt);
            for(int j = crossover; j < brainWeights.size(); j++)
            {
                brainWeights[j] = matingBrainWeights[j];
            }
            brain.setWeights(brainWeights);

}

void animal::mutate()
{
    std::vector<float> brainWeights; brain.getWeights(brainWeights);

    std::uniform_int_distribution<int> uniform_dist(0, brainWeights.size());
    std::uniform_real_distribution<float> float_dist(-3.2, 3.2);
    float mutateFactor = float_dist(mt);
    int mutatedWeightId = uniform_dist(mt);

    brainWeights[mutatedWeightId] = (brainWeights[mutatedWeightId] * mutateFactor) / 2.0;
    brain.setWeights(brainWeights);

}

void animal::setNewBrainWeights(std::vector<float>& newWeights)
{
    brain.setWeights(newWeights);
}

void animal::resetBrain()
{
    std::vector<float> brainWeights; brain.getWeights(brainWeights);

    std::uniform_real_distribution<float> new_weight(-3.2, 3.2);
    for(int i = 0; i < brainWeights.size(); i++)
    {
        brainWeights[i] = new_weight(mt);
    }

    brain.setWeights(brainWeights);

}

void animal::resetFitnessScore()
{
    fitnessScore = 0;
}

void animal::draw(sf::RenderWindow& window)
{
      window.draw(this->shape);
}

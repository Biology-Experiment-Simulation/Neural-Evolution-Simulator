#include "Simulation.h"

Simulation::Simulation()
{
    this->input.resize(4);

    //sf::CircleShape animal[10];
    ///sf::CircleShape food[10];
   // this->window = sf::RenderWindow(sf::VideoMode(800, 600, 32), "Neural-Evolution balls");
  //  this->window.setVerticalSyncEnabled(true);
}

Simulation::~Simulation()
{
    //dtor
}

float Simulation::distance(float x1, float x2, float y1, float y2)
    {
        float diffY = y1 - y2;
        float diffX = x1 - x2;
        return sqrt((diffY * diffY) + (diffX * diffX));
    }

void Simulation::createFood(){
     for (int i=0;i<10;i++){
    this->food[i].setRadius(10 + 4);
    this->food[i].setOutlineThickness(2);
    this->food[i].setOutlineColor(sf::Color::Black);
    this->food[i].setFillColor(sf::Color::Green);
    this->food[i].setOrigin(10 / 2, 10 / 2);
    this->food[i].setPosition(rands(0,800),rands(0,600));
    }
    std::cout << " cross "  << " ;";
}

        // Create the food
void Simulation::createAnimals(){
    this->firstBest = 0; this->secondBest = 0;/// INPUTS
    for(int i=0;i<10;i++){
       NN::Net c(4,3,7,2);
        this->brains.push_back(c);
    }

    for (int i=0;i<10;i++){
     this->animal[i].setRadius(10 + 3);
     this->animal[i].setOutlineThickness(2);
     this->animal[i].setOutlineColor(sf::Color::Black);
     this->animal[i].setFillColor(sf::Color(rands(210,255),rands(110,255),rands(0,255)));
     this->animal[i].setOrigin(10 / 2, 10 / 2);
     this->animal[i].setPosition(rands(0,800),rands(0,600));
    }

    std::cout << " dsdsddd "  << " ;";
    }


void Simulation::evolve()
{
    int crossover = uniform_dist(mt);int mutate = uniform_dist(mt);

    this->brains[this->firstBest].getWeights(this->bestWeights);
    this->brains[this->secondBest].getWeights(this->secondbestWeights);

    std::vector<float> temps; temps.resize(this->bestWeights.size());
    for(int i=5; i<8;i++)
        {
            crossover = uniform_dist(mt);
            std::cout << " cross " << crossover << " ;";
            for(int j=0;j<temps.size();j++)
            {
                if(crossover>j)
                {temps[j]=this->bestWeights[j];}else
                temps[j]=this->secondbestWeights[j];
            }
            this->brains[i].setWeights(temps);
        }

        this->brains[0].setWeights(this->bestWeights);
        this->brains[1].setWeights(this->bestWeights);
        this->brains[2].setWeights(this->secondbestWeights);

        secondbestWeights[mutate] =randomVal(mt);
        this->brains[3].setWeights(this->secondbestWeights);
        this->bestWeights[mutate] =randomVal(mt);
        this->brains[4].setWeights(this->bestWeights);

     for(int i=0;i<temps.size();i++){
        temps[i] = randomVal(mt);}
     this->brains[8].setWeights(temps);
    for(int i=0;i<temps.size();i++){
        temps[i] = randomVal(mt);}
    this->brains[9].setWeights(temps);

}

void Simulation::setClosestFood(int creatureId)
{
    float closestDistance=99999;
    int closestId;
    float tempdist;
    for(int i = 0; i<10; i++)
    {
       tempdist = distance(this->food[i].getPosition().x, this->animal[creatureId].getPosition().x,this->food[i].getPosition().y, this->animal[creatureId].getPosition().y);
       if(tempdist < closestDistance)
       {
           closestDistance = tempdist;
           closestId = i;
       }
    }
    this->brains[creatureId].closestFood = closestId;

}


void Simulation::proccessCreatures()
{
     for(int i=0;i<this->brains.size();i++)
                    {
                        int j = this->brains[i].closestFood;
                        //std::cout << j ;
                        if(this->food[j].getPosition().x < animal[i].getPosition().x){/// na lewo
                            this->input[0]=1.0f;this->input[1]=-1.0f;
                        }else if(this->food[j].getPosition().x > this->animal[i].getPosition().x){ /// na prawo
                            this->input[0]=-1.0f;this->input[1]=1.0f;
                        }
                        /// Creatures Brain inputs/ outputs
                         if(this->food[j].getPosition().y < this->animal[i].getPosition().y){   /// nizej
                            this->input[2]=1.0f;this->input[3]=-1.0f;
                        }else if(this->food[j].getPosition().y > this->animal[i].getPosition().y){  /// wyzej
                            this->input[2]=-1.0f;this->input[3]=1.0f;
                        }
                         this->output = this->brains[i].feedForward(this->input);
                        this->animal[i].move(this->output[0]*4,this->output[1]*4);

                        ///  creatures Brains Fitness Scoring
                          if (distance(this->food[j].getPosition().x, this->animal[i].getPosition().x,this->food[j].getPosition().y, this->animal[i].getPosition().y) < 850)
                        {
                            this->brains[i].fitnessScore+= -1;

                        }
                         if (distance(this->food[j].getPosition().x, this->animal[i].getPosition().x,this->food[j].getPosition().y, this->animal[i].getPosition().y) < 450)
                        {
                            this->brains[i].fitnessScore+= 1;

                        }
                        if (distance(this->food[j].getPosition().x, this->animal[i].getPosition().x,this->food[j].getPosition().y, this->animal[i].getPosition().y) < 200)
                        {
                            this->brains[i].fitnessScore+= 2;
                        }
                        if (distance(this->food[j].getPosition().x, this->animal[i].getPosition().x,this->food[j].getPosition().y, this->animal[i].getPosition().y) < 50)
                        {
                            this->brains[i].fitnessScore+= 4;
                        }
                        if (distance(this->food[j].getPosition().x, this->animal[i].getPosition().x,this->food[j].getPosition().y, this->animal[i].getPosition().y) < 30)
                        {
                            this->brains[i].fitnessScore+= 6;
                        }
                        if (distance(this->food[j].getPosition().x, this->animal[i].getPosition().x,this->food[j].getPosition().y, this->animal[i].getPosition().y) < 15)
                        {
                            this->brains[i].fitnessScore+= 7;
                        }

                        if (distance(this->food[j].getPosition().x, this->animal[i].getPosition().x,this->food[j].getPosition().y, this->animal[i].getPosition().y) < 10)
                        {
                            this->brains[i].fitnessScore+= 233;
                            this->food[j].setPosition(rands(0,800),rands(0,600));
                             for (int i=0;i<10;i++){
                            setClosestFood(i);
                        }


                        }

                    }
}

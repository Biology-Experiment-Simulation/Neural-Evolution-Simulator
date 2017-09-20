#include "Simulation.h"

Simulation::Simulation()
{
    this->input.resize(4);
}

Simulation::~Simulation()
{

}

float Simulation::distance(float x1, float x2, float y1, float y2)
    {
        float diffY = y1 - y2;
        float diffX = x1 - x2;
        return sqrt((diffY * diffY) + (diffX * diffX));
    }
float Simulation::distance(std::vector<int> animalPos, std::vector<int> FoodPos)
    {
        float diffY = animalPos[1] - FoodPos[1];
        float diffX = animalPos[0] - FoodPos[0];
        return sqrt((diffY * diffY) + (diffX * diffX));
    }

void Simulation::createFood(int number){

    this->foods.resize(number);

     for (int i=0;i<10;i++){
    this->foody[i].setRadius(10 + 4);
    this->foody[i].setOutlineThickness(2);
    this->foody[i].setOutlineColor(sf::Color::Black);
    this->foody[i].setFillColor(sf::Color::Green);
    this->foody[i].setOrigin(10 / 2, 10 / 2);
    this->foody[i].setPosition(rands(0,800),rands(0,600));
    }
    std::cout << " created "  << number << " animals" << "/n" ;
}

void Simulation::createAnimals(int number){
    //this->firstBest = 0; this->secondBest = 0;/// INPUTS
    this->animals.resize(number);

    for(int i=0;i<10;i++){
       std::shared_ptr<NN::Net> c(new NN::Net(4,3,7,2));
        this->brains.push_back(c);
    }

    for (int i=0;i<10;i++){
     animaly[i].setRadius(10 + 3);
     animaly[i].setOutlineThickness(2);
     animaly[i].setOutlineColor(sf::Color::Black);
     animaly[i].setFillColor(sf::Color(rands(210,255),rands(110,255),rands(0,255)));
     animaly[i].setOrigin(10 / 2, 10 / 2);
     animaly[i].setPosition(rands(0,800),rands(0,600));
    }

    std::cout << " dsdsddd "  << " ;";
    }

void Simulation::evolve()
{
    int crossover = uniform_dist(mt);int mutate = uniform_dist(mt);

    (*brains[firstBest]).getWeights(bestWeights);
    (*brains[this->secondBest]).getWeights(this->secondbestWeights);

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
            (*brains[i]).setWeights(temps);
        }

        (*brains[0]).setWeights(this->bestWeights);
        (*brains[1]).setWeights(this->bestWeights);
        (*brains[2]).setWeights(this->secondbestWeights);

        secondbestWeights[mutate] =randomVal(mt);
        (*brains[3]).setWeights(this->secondbestWeights);
        this->bestWeights[mutate] =randomVal(mt);
        (*brains[4]).setWeights(this->bestWeights);

     for(int i=0;i<temps.size();i++){
        temps[i] = randomVal(mt);}
     (*brains[8]).setWeights(temps);
    for(int i=0;i<temps.size();i++){
        temps[i] = randomVal(mt);}
    (*brains[9]).setWeights(temps);

}

void Simulation::setClosestFood(int creatureId)
{
    float closestDistance=99999;
    int closestId;
    float tempdist;
    for(int i = 0; i<10; i++)
    {
       tempdist = distance(foody[i].getPosition().x, animaly[creatureId].getPosition().x, foody[i].getPosition().y, animaly[creatureId].getPosition().y);
       if(tempdist < closestDistance)
       {
           closestDistance = tempdist;
           closestId = i;
       }
    }
    (*brains[creatureId]).closestFood = closestId;

}

void Simulation::setTwoBestAnimals()
{
    std::cout << "fitness scores" << std::endl;
    int c =0;
    int scoreA=-4000;
    int scoreB=-4000;
    for (auto& it : brains)
    {
        std::cout << (*it).fitnessScore << std::endl;
        if((*it).fitnessScore > scoreA)
        {
            scoreA = (*it).fitnessScore;
            scoreB = scoreA;
            this->secondBest = this->firstBest;
            this->firstBest = c;
        }
        else if((*it).fitnessScore > scoreB)
        {
            scoreB = (*it).fitnessScore;
            this->secondBest = c;
        }
        c++;
    }
    std::cout << "first best = " << this->firstBest << "second best = " << this->secondBest << std::endl;
}

void Simulation::proccessCreatures()
{
     for(int i=0; i<brains.size(); i++)
                    {
                        int j = (*brains[i]).closestFood;

                        if(this->foody[j].getPosition().x < animaly[i].getPosition().x){/// na lewo
                            this->input[0]=1.0f;this->input[1]=-1.0f;
                        }else if(this->foody[j].getPosition().x > this->animaly[i].getPosition().x){ /// na prawo
                            this->input[0]=-1.0f;this->input[1]=1.0f;
                        }
                        /// Creatures Brain inputs/ outputs
                         if(this->foody[j].getPosition().y < this->animaly[i].getPosition().y){   /// nizej
                            this->input[2]=1.0f;this->input[3]=-1.0f;
                        }else if(this->foody[j].getPosition().y > this->animaly[i].getPosition().y){  /// wyzej
                            this->input[2]=-1.0f;this->input[3]=1.0f;
                        }
                         this->output = (*brains[i]).feedForward(this->input);
                        this->animaly[i].move(this->output[0]*4,this->output[1]*4);

                        ///  creatures Brains Fitness Scoring
                          if (distance(this->foody[j].getPosition().x, this->animaly[i].getPosition().x,this->foody[j].getPosition().y, this->animaly[i].getPosition().y) < 850)
                        {
                            (*brains[i]).fitnessScore+= -1;

                        }
                         if (distance(this->foody[j].getPosition().x, this->animaly[i].getPosition().x,this->foody[j].getPosition().y, this->animaly[i].getPosition().y) < 450)
                        {
                            (*brains[i]).fitnessScore+= 1;

                        }
                        if (distance(this->foody[j].getPosition().x, this->animaly[i].getPosition().x,this->foody[j].getPosition().y, this->animaly[i].getPosition().y) < 200)
                        {
                            (*brains[i]).fitnessScore+= 2;
                        }
                        if (distance(this->foody[j].getPosition().x, this->animaly[i].getPosition().x,this->foody[j].getPosition().y, this->animaly[i].getPosition().y) < 50)
                        {
                            (*brains[i]).fitnessScore+= 4;
                        }
                        if (distance(this->foody[j].getPosition().x, this->animaly[i].getPosition().x,this->foody[j].getPosition().y, this->animaly[i].getPosition().y) < 30)
                        {
                            (*brains[i]).fitnessScore+= 6;
                        }
                        if (distance(this->foody[j].getPosition().x, this->animaly[i].getPosition().x,this->foody[j].getPosition().y, this->animaly[i].getPosition().y) < 15)
                        {
                            (*brains[i]).fitnessScore+= 7;
                        }

                        if (distance(this->foody[j].getPosition().x, this->animaly[i].getPosition().x,this->foody[j].getPosition().y, this->animaly[i].getPosition().y) < 10)
                        {
                            (*brains[i]).fitnessScore+= 233;
                            this->foody[j].setPosition(rands(0,800),rands(0,600));
                             for (int i=0;i<10;i++){
                            setClosestFood(i);
                        }


                        }

                    }
}

void Simulation::runSimulation(sf::RenderWindow& window)
{
    bool isPlaying = false;
    sf::Clock AITimer;
    const sf::Time AITime = sf::seconds(0.004f);
    //sf::View view1(sf::FloatRect(200, 200, 800, 600));
    //window.setView(view1);

    while (window.isOpen())
    {
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

        if (!isPlaying)
        {
            isPlaying = true;
            for (int i=0; i<10; i++)
            {
                this->foody[i].setPosition(rands(0,800),rands(0,600));
            }
            for (int i=0; i<10; i++)
            {
                this->animaly[i].setPosition(rands(0,800),rands(0,600));
                this->setClosestFood(i);
            }
        }

        if (isPlaying)
        {
            if (AITimer.getElapsedTime() > AITime)
            {
                /// One Generation time
                this->simulationTime--;
                if(this->simulationTime == 0)
                {
                    this->setTwoBestAnimals();
                    this->evolve();

                    for(int i=0; i<10; i++)
                    {
                        this->animaly[i].setPosition(rands(0,800),rands(0,600));
                        (*brains[i]).fitnessScore = 0;
                    }
                    this->firstBest = 0;
                    this->secondBest = 0;
                    this->simulationTime =1499;
                    isPlaying = false;
                }
                if(this->simulationTime%500 == 0)
                {
                    for (int i=0; i<10; i++)
                    {
                        this->foody[i].setPosition(rands(0,800),rands(0,600));
                    }
                    for (int i=0; i<10; i++)
                    {
                        this->animaly[i].setPosition(rands(444,600),rands(200,500));
                        this->setClosestFood(i);
                    }
                }
                AITimer.restart();
                this->proccessCreatures();

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
            }
        }
        /// RENDER ALL /////////////////////////////////
        window.clear(sf::Color(20, 10, 250));
        for(int i=0; i<brains.size(); i++)
        {
            window.draw(this->animaly[i]);
            window.draw(this->foody[i]);
        }
        window.display();
    }
}


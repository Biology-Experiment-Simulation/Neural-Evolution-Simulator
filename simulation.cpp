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
float Simulation::distance(std::vector<float> animalPos, std::vector<float> FoodPos)
    {
        float diffY = animalPos[1] - FoodPos[1];
        float diffX = animalPos[0] - FoodPos[0];
        return sqrt((diffY * diffY) + (diffX * diffX));
    }

void Simulation::createFood(int number)
{

    for(int i=0;i<number;i++){
       std::shared_ptr<food> f(new food());
        this->foods.push_back(f);
    }
    std::cout << " created "  << number << "new food" << "\n" ;
}

void Simulation::createAnimals(int number)
{
    for(int i=0;i<number;i++)
        {
       std::shared_ptr<animal> a(new animal());
        this->animals.push_back(a);
        }
    }

void Simulation::evolve()
{
   // int crossover = uniform_dist(mt);int mutate = uniform_dist(mt);

    (*animals[firstBest]).brain.getWeights(bestWeights);
    (*animals[secondBest]).brain.getWeights(secondbestWeights);

    (*animals[0]).setNewBrainWeights(bestWeights);
    (*animals[1]).setNewBrainWeights(secondbestWeights);


    for(unsigned i =2; i < animals.size() - 2; i++)
    {
        (*animals[i]).crossover((*animals[0]));
    }

    (*animals[animals.size()-1]).resetBrain();
    (*animals[animals.size()-2]).resetBrain();
}

void Simulation::setClosestFood(int creatureId)
{
     int closestId;
     float closestDistance=99999;
     float tempdistance; unsigned tempId = 0;
     for (auto& food : foods)
     {
        tempdistance = distance((*animals[creatureId]).getPosition(),(*food).getPosition());
        if(tempdistance < closestDistance)
       {
           closestDistance = tempdistance;
           closestId = tempId;
       }
       tempId++;
     }
     (*animals[creatureId]).closestFood = closestId;

}

void Simulation::setTwoBestAnimals()
{
    int c =0;
    int scoreA=-4000;
    int scoreB=-4000;
        std::cout << "fitness scores" << "\n";
    for (auto& animal : animals )
    {
        std::cout << (*animal).fitnessScore << "\n";
        if((*animal).fitnessScore > scoreA)
        {
            scoreA = (*animal).fitnessScore;
            scoreB = scoreA;
            this->secondBest = this->firstBest;
            this->firstBest = c;
        }
        else if((*animal).fitnessScore > scoreB)
        {
            scoreB = (*animal).fitnessScore;
            this->secondBest = c;
        }
        c++;
    }
std::cout << "first best = " << this->firstBest << "second best = " << this->secondBest << "\n";



}

void Simulation::proccessCreatures()
{
    unsigned animalID = 0;
    std::vector<float> closestFoodPos, animalPos;
     for (auto& animal : animals)
    {
        setClosestFood(animalID);
        unsigned closestFoodId = (*animal).closestFood;

        closestFoodPos = (*foods[closestFoodId]).getPosition();
        animalPos = (*animal).getPosition();

        if( closestFoodPos[0] < animalPos[0] ){/// na lewo
            this->input[0]=1.0f + randomInput(mt);this->input[1]=-1.0f + randomInput(mt);
        }else if(closestFoodPos[0] > animalPos[0]){ /// na prawo
            this->input[0]=-1.0f + randomInput(mt);this->input[1]=1.0f + randomInput(mt);
        }

        if( closestFoodPos[1] < animalPos[1] ){ /// nizej
            this->input[2]=1.0f + randomInput(mt);this->input[3]=-1.0f + randomInput(mt);
        }else if(closestFoodPos[1] > animalPos[1]){ /// wyzej
            this->input[2]=-1.0f + randomInput(mt) ;this->input[3]=1.0f + randomInput(mt);
        }
        (*animal).runAnimal(input);

        ///  creatures Fitness Scoring
        if (distance(animalPos, closestFoodPos) < 850)
        {
            (*animal).fitnessScore+= -1;

        }
        if (distance(animalPos, closestFoodPos) < 450)
        {
            (*animal).fitnessScore+= 1;

        }
        if (distance(animalPos, closestFoodPos) < 200)
        {
            (*animal).fitnessScore+= 2;
        }
        if (distance(animalPos, closestFoodPos) < 50)
        {
            (*animal).fitnessScore+= 4;
        }
        if (distance(animalPos, closestFoodPos) < 30)
        {
            (*animal).fitnessScore+= 6;
        }
        if (distance(animalPos, closestFoodPos) < 15)
        {
            (*animal).fitnessScore+= 7;
        }

        if (distance(animalPos, closestFoodPos) < 10)
        {
            (*animal).fitnessScore+= 233;
            (*foods[closestFoodId]).setPosition(rands(0,800),rands(0,600));
            unsigned izz = 0;
            for(auto& animal : animals)
            {
                setClosestFood(izz);
                izz++;
            }

        }
        animalID++;
    }
}

void Simulation::runSimulation(sf::RenderWindow& window)
{
    bool isPlaying = false;
    sf::Clock AITimer;
    const sf::Time AITime = sf::seconds(0.004f);
    float testx = 1.0f;
    float testy = 1.0f;
    sf::View view1(sf::FloatRect(2, 2, 800, 600));
    view1.zoom(4.0f);
    window.setView(view1);

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

            if (event.type == sf::Event::EventType::KeyPressed){
                if (event.key.code == sf::Keyboard::Down)
                {
                view1.zoom(0.994f);
                window.setView(view1);
                }
                if (event.key.code == sf::Keyboard::Up)
                {
                view1.zoom(1.004f);
                window.setView(view1);
                }
            }
        }

        if (!isPlaying)
        {
            isPlaying = true;
            for(auto& food : foods)
            {
                (*food).setPosition(rands(0,800),rands(0,600));
            }
            for(auto& animal : animals)
            {
                (*animal).setPosition(rands(0,800),rands(0,600));
                (*animal).resetFitnessScore();
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

                    for(auto& animal : animals)
                    {
                        (*animal).setPosition(rands(0,800),rands(0,600));
                        (*animal).resetFitnessScore();
                    }

                    this->firstBest = 0;
                    this->secondBest = 0;
                    this->simulationTime =1499;
                    isPlaying = false;
                }
                if(this->simulationTime%500 == 0)
                {
                    for(auto& food : foods)
                    {
                        (*food).setPosition(rands(0,800),rands(0,600));
                    }
                    unsigned i = 0;
                    for(auto& animal : animals)
                    {
                        (*animal).setPosition(rands(0,800),rands(0,600));
                         setClosestFood(i); i++;
                    }

                }
                AITimer.restart();
                this->proccessCreatures();

            }
        }
        /// RENDER ALL /////////////////////////////////
        window.clear(sf::Color(20, 10, 250));

        for(auto& animal : animals)
        {
            (*animal).draw(window);
        }
        for(auto& food : foods)
        {
            (*food).draw(window);
        }
        window.display();
    }
}


#include "food.h"

food::food()
{
    this->shape.setRadius(10);
    this->shape.setOutlineThickness(2);
    this->shape.setOutlineColor(sf::Color::Green);
    this->shape.setFillColor(sf::Color::Green);
    this->shape.setOrigin(10 / 2, 10 / 2);
    this->shape.setPosition(rands(0,800),rands(0,600));
    std::cout << "default food created !" << "\n";
}

food::~food()
{
    //dtor
}

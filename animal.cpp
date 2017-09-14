#include "animal.h"

animal::animal() : brain(NN::Net(4,2,7,2))
{
    //ctor
}

animal::~animal()
{
    //dtor
}

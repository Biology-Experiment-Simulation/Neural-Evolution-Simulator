#pragma once
#include <cmath>
#include <cstdlib>

static float rands(float a, float b)
{
    return ((b-a)*((float)rand()/RAND_MAX))+a;
}

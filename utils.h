#pragma once
#include <cmath>
#include <cstdlib>
#include <random>

/// .......... Random functions Data .............. //////////////
 static std::random_device rd;
 static std::mt19937 mt(rd());

static float rands(float a, float b)
{
    return ((b-a)*((float)rand()/RAND_MAX))+a;
}

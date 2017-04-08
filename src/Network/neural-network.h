
#pragma once

#include "Common.h"

class NeuralNetwork
{
public:
    virtual ~NeuralNetwork() = default;
    virtual NeuralNetwork * train(int) = 0;
    virtual double fx(double) = 0;
};

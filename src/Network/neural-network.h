
#pragma once

#include "Common.h"

class ArtificalNeuralNetwork 
{
public:
    virtual ~ArtificalNeuralNetwork() = default;
	virtual ArtificalNeuralNetwork * train(int) = 0;
	virtual double fx(double) = 0;
};


#pragma once

#include "neural-network.h"
#include "mlp.h"
#include "nodes.h"

class RBF : public NeuralNetwork  
{
    HiddenLayerRBF hiddenLayer;
	TrainingData trainingSet;
	ReceptorNode inputLayer;
	ResultNode outputLayer;
    SpaceFunc spaceFunc;

    double errorThreshold;
    double learningRate;
public:
	RBF();
	virtual ~RBF();

	RBF* setSpaceFunction(SpaceFunc function);
	RBF* setTrainingData(TrainingData set);
	RBF* setErrorThreshold(double);
	RBF* setLearningRate(double);
	RBF* setupHiddenLayer();
	RBF* train(int);

	double fx(double);
};

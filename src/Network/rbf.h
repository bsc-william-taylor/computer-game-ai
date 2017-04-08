
#pragma once

#include "neural-network.h"
#include "mlp.h"
#include "Nodes.h"

class RadicalBasisFunction : public ArtificalNeuralNetwork  
{
private:
	std::function<double(double, double)> spaceFunc;
	std::vector<FunctionNode *> hiddenLayer;
	std::vector<Point> trainingSet;
	
	ReceptorNode * inputLayer;
	ResultNode * outputLayer;
public:
	RadicalBasisFunction();
	~RadicalBasisFunction();

	RadicalBasisFunction * setSpaceFunction(std::function<double(double, double)>);
	RadicalBasisFunction * setTrainingData(TrainingSet set);
	RadicalBasisFunction * setErrorThreshold(double);
	RadicalBasisFunction * setLearningRate(double);
	RadicalBasisFunction * setupHiddenLayer();
	RadicalBasisFunction * train(int);

	double fx(double);
private:
	double errorThreshold;
	double learningRate;
};

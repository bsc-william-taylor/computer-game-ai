
#pragma once

#include "neural-network.h"
#include "Nodes.h"
#include "Graph.h"

class MultiLayeredPercepton : public ArtificalNeuralNetwork 
{
private:
	double errorThreshold;
	double learningRate;
public:
	MultiLayeredPercepton();
	~MultiLayeredPercepton();

	MultiLayeredPercepton * setOutputLayer(std::vector<OutputNode *>);
	MultiLayeredPercepton * setHiddenLayer(std::vector<HiddenNode *>);
	MultiLayeredPercepton * setInputLayer(std::vector<InputNode *>);
	MultiLayeredPercepton * setTrainingSet(std::vector<Point>);
	MultiLayeredPercepton * setErrorThreshold(double);
	MultiLayeredPercepton * setLearningRate(double);
	MultiLayeredPercepton * train(int);
private:
	std::vector<HiddenNode *> hiddenNeurons;
	std::vector<OutputNode *> outputNeurons;
	std::vector<InputNode *> inputNeurons;
	std::vector<Point> trainingSet;
public:
	double fx(double);
private:
	int chooseInputPattern(int, std::vector<bool>& vec);
};

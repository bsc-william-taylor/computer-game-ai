
#pragma once

#include "neural-network.h"
#include "Nodes.h"
#include "Graph.h"

class MLP : public NeuralNetwork 
{
    TrainingData trainingSet;
    HiddenLayerMLP hiddenNeurons;
    OutputLayer outputNeurons;
    InputLayer inputNeurons;

	double errorThreshold;
	double learningRate;
public:
	MLP();
	virtual ~MLP();

    int chooseInputPattern(int, std::vector<bool>& vec);

	MLP* setOutputLayer(OutputLayer outputLayer);
	MLP* setHiddenLayer(HiddenLayerMLP hiddenLayer);
	MLP* setInputLayer(InputLayer inputLayer);
	MLP* setTrainingSet(TrainingData trainingSet);
	MLP* setErrorThreshold(double);
	MLP* setLearningRate(double);
	MLP* train(int);

	double fx(double);
};

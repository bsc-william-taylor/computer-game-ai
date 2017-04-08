
#include "rbf.h"

RadicalBasisFunction::RadicalBasisFunction()
{
	outputLayer = new ResultNode();
	inputLayer = new ReceptorNode();

	errorThreshold = 0.01;
	learningRate = 0.2;
}

RadicalBasisFunction::~RadicalBasisFunction()
{
	for (auto& neuron : hiddenLayer) {
		delete neuron;
	}

	delete outputLayer;
	delete inputLayer;
}

double RadicalBasisFunction::fx(double x)
{ 
	inputLayer->setValue(x);

	for (auto& hiddenNeuron : hiddenLayer) {
		inputLayer->feedForward(hiddenNeuron);
		hiddenNeuron->feedForward(outputLayer);
	}

	return outputLayer->getValue(); 
}

RadicalBasisFunction * RadicalBasisFunction::setErrorThreshold(double error)
{
	errorThreshold = error;
	return this;
}

RadicalBasisFunction * RadicalBasisFunction::setLearningRate(double rate)
{
	learningRate = rate;
	return this;
}

RadicalBasisFunction * RadicalBasisFunction::setupHiddenLayer()
{
	for (unsigned i = 0; i < trainingSet.size(); i++) {
		hiddenLayer.push_back(new FunctionNode(spaceFunc));
		hiddenLayer[i]->setCenter(trainingSet[i].x);
	}

	return this;
}

RadicalBasisFunction * RadicalBasisFunction::setTrainingData(TrainingSet set)
{
	trainingSet = std::vector<Point>(set);
	return this;
}

RadicalBasisFunction * RadicalBasisFunction::setSpaceFunction(std::function<double(double, double)> func)
{
	spaceFunc = func;
	return this;
}

RadicalBasisFunction * RadicalBasisFunction::train(int iterations)
{ 
	for (int i = 0; i < iterations;) {
		unsigned trains = 0;
		while (trains < trainingSet.size()) {
			Point& point = trainingSet[trains];
			inputLayer->setValue(point.x);
			i++;

			for (auto& hiddenNeuron : hiddenLayer) {
				inputLayer->feedForward(hiddenNeuron);
				hiddenNeuron->feedForward(outputLayer);
			}

			double error = outputLayer->getError(point.y);

			if (abs(error) <= errorThreshold) {
				trains++;
			} else {
				for (auto& hiddenNeuron : hiddenLayer) {
					hiddenNeuron->adjustWeights(learningRate, error);
				}
			}
		}
	}

	return this;
}

/**
 * 
 * Copyright 2015 : William Taylor : wi11berto@yahoo.co.uk
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * 	http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "RadialBasisFunction.h"
#include "HiddenNode.h"

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

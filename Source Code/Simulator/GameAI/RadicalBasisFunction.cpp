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

#include "RadicalBasisFunction.h"
#include "HiddenNode.h"

RadicalBasisFunction::RadicalBasisFunction()
{
	outputLayer = new ResultNode();
	inputLayer = new ReceptorNode();

	errorThreshold = 0.01;
	learningRate = 0.01;
}

RadicalBasisFunction::~RadicalBasisFunction()
{
	delete outputLayer;
	delete inputLayer;
}

double RadicalBasisFunction::fx(double x)
{ 
	inputLayer->setValue(x);
	inputLayer->feedForward(hiddenLayer[0]);

	for (auto& hiddenNode : hiddenLayer) {
		hiddenNode->feedForward(outputLayer);
	}

	return outputLayer->getValue(); 
}

RadicalBasisFunction * RadicalBasisFunction::setupHiddenLayer()
{
	for (int i = 0; i < trainingSet.size(); i++) {
		hiddenLayer.push_back(new FunctionNode(spaceFunc));
	}

	return this;
}

RadicalBasisFunction * RadicalBasisFunction::setTrainingData(TrainingSet set)
{
	this->trainingSet = std::vector<GraphPoint>(set);

	return this;
}

RadicalBasisFunction * RadicalBasisFunction::setSpaceFunction(std::function<double(double)> func)
{
	spaceFunc = func;

	return this;
}

RadicalBasisFunction * RadicalBasisFunction::train(int iterations)
{
	std::vector<bool> testsCompleted;
	testsCompleted.resize(trainingSet.size());
	for (auto& v : testsCompleted) {
		v = false;
	}

	int randomTestID = 0;

	while (true) {
		GraphPoint& point = trainingSet[randomTestID];

		inputLayer->setValue(point.x);
		inputLayer->feedForward(hiddenLayer[randomTestID]);
		hiddenLayer[randomTestID]->feedForward(outputLayer);

		double error = outputLayer->getError(point.y);

		if (abs(error) <= errorThreshold) {
		//	DEBUG("Converged");
		
			testsCompleted[randomTestID] = true;
			int totalTests = 0;
			for (auto& v : testsCompleted) {
				if (v) totalTests++;
			}

			if (totalTests == testsCompleted.size()) {
				break;
			} else {
				if (randomTestID < trainingSet.size() - 1) {
					randomTestID++;
				} else {
					randomTestID = 0;
				}
			}
		} else {
			for (auto& func : this->hiddenLayer)
			{
				func->adjustWeights(learningRate, error);
			}
		}
	}

	return this;
}

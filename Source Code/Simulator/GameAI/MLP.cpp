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

#include "MLP.h"

MLP::MLP()
	: errorThreshold(0.05), learningRate(0.2)
{
}

MLP::~MLP()
{
}

MLP * MLP::setErrorThreshold(double err)
{
	errorThreshold = err;
	return this;
}

MLP * MLP::setLearningRate(double rate)
{
	learningRate = rate;
	return this;
}

MLP * MLP::setOutputLayer(std::vector<OutputNode *>& vec)
{
	outputNeurons = std::vector<OutputNode *>(vec);
	return this;
}

MLP * MLP::setHiddenLayer(std::vector<HiddenNode *>& vec)
{
	hiddenNeurons = std::vector<HiddenNode *>(vec);
	return this;
}

MLP * MLP::setInputLayer(std::vector<InputNode *>& vec)
{
	inputNeurons = std::vector<InputNode *>(vec);
	return this;
}

MLP * MLP::learnMapping(int iterations)
{
	std::vector<bool> testsCompleted;
	testsCompleted.resize(trainingSet.size());
	for (auto& v : testsCompleted) {
		v = false;
	}

	int randomTestID = rand() % trainingSet.size();

	while (--iterations != 0) {
		GraphPoint& test = trainingSet[randomTestID];	
		inputNeurons[0]->setValue(test.x);

		for (auto& hiddenNode : hiddenNeurons) {
			hiddenNode->feedForward(inputNeurons);
		}

		outputNeurons[0]->finish(hiddenNeurons);

		// if within the error margin
		if (abs(test.y - outputNeurons[0]->getValue()) <= errorThreshold) {
			testsCompleted[randomTestID] = true;
			int totalTests = 0;
			for (auto& v : testsCompleted) {
				if (v) totalTests++;
			}

			if (totalTests == testsCompleted.size()){
				break;
			} else {
				int previous = randomTestID;
				do {
					randomTestID = rand() % trainingSet.size();
				} while (previous == randomTestID);
			}
		} else {
			// Reset previous test passes
			for (auto& v : testsCompleted) {
				v = false;
			}

			// calculate the error in the network
			outputNeurons[0]->calculateError(test.y); 
			// then get the error
			double error = outputNeurons[0]->getError();
			// Adjust weights in the hidden neuron
			for (auto & neuron : hiddenNeurons){
				neuron->calculateError(outputNeurons[0], error);
				neuron->adjustWeight(outputNeurons[0], learningRate, error);
			}

			// Adjust the weights in the input neuron
			for (int i = 0; i < hiddenNeurons.size(); i++) {
				error = hiddenNeurons[i]->getError();
				for (auto & neuron : inputNeurons){
					neuron->adjustWeight(hiddenNeurons[i], learningRate, error);
				}
			}
		}
	}

	return this;
}

MLP * MLP::setTrainingSet(std::vector<GraphPoint>& point)
{
	this->trainingSet = point;

	return this;
}

double MLP::fx(double x)
{
	inputNeurons[0]->setValue(x);

	for (auto& hiddenNode : hiddenNeurons) {
		hiddenNode->feedForward(inputNeurons);
	}

	outputNeurons[0]->finish(hiddenNeurons);
	return outputNeurons[0]->getValue();
}

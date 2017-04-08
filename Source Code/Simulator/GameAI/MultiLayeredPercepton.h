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

#pragma once

#include "ArtificalNeuralNetwork.h"
#include "OutputNode.h"
#include "HiddenNode.h"
#include "InputNode.h"
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

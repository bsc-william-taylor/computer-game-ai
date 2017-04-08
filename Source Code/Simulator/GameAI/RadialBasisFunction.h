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
#include "MultiLayeredPercepton.h"
#include "FunctionNode.h"
#include "ReceptorNode.h"
#include "ResultNode.h"

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

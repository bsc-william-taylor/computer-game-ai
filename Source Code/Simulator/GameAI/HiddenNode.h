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

#include "Common.h"

class OutputNode;
class InputNode;

class HiddenNode 
{
private:
	std::function<double(std::vector<InputNode *>&, HiddenNode *)> activationFunction;
	std::vector<OutputNode *> outputNodes;
	std::vector<double> weights;

	bool _bias;
	double error;
	double value;
public:
	HiddenNode();
	~HiddenNode();

	std::function<double(std::vector<InputNode *>&, HiddenNode *)> getFunction() {
		return activationFunction;
	}

	void setActivationFunction(std::function<double(std::vector<InputNode *>, HiddenNode *)>);
	void feedForwardTo(OutputNode *);
	void feedForward(std::vector<InputNode *>&);	
	
	void calculateError(OutputNode * node, double outputError);
	void adjustWeight(OutputNode * node, double learning, double error);
	void setValue(double);
	void makeBias() {
		_bias = true;
		value = 1.0;
	}

	bool isBias() {
		return _bias;
	}

	double getError();
	double& getWeight(OutputNode * node);
	double getValue();
};

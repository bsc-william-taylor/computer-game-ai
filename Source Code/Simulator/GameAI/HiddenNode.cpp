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

#include "HiddenNode.h"
#include "InputNode.h"
#include "OutputNode.h"

HiddenNode::HiddenNode()
	:  value(0.0)
{
	_bias = false;
}

HiddenNode::~HiddenNode()
{
}

void HiddenNode::setActivationFunction(std::function<double(std::vector<InputNode *>, HiddenNode *)> a)
{
	this->activationFunction = a;
}

void HiddenNode::feedForwardTo(OutputNode * node)
{
	float f = 0;
	//do {
		f = static_cast <float>(rand()) / (static_cast <float> (RAND_MAX / 1.0));
	//} while (f < 0.0001);

	outputNodes.push_back(node);
	weights.push_back(f);
}

void HiddenNode::setValue(double v)
{
	this->value = v;
}

void HiddenNode::feedForward(std::vector<InputNode *>& inputs)
{
	value = (activationFunction(inputs, this));
}

void HiddenNode::calculateError(OutputNode * node, double outputError)
{
	//error = outputError *  getWeight(node) * (1 - pow(value, 2.0));
	error = outputError * getWeight(node) * value * (1 - value);
}

void HiddenNode::adjustWeight(OutputNode * node, double learning, double totalError)
{
	double& weight = getWeight(node);
	weight = weight + (learning * totalError * value);
}

double& HiddenNode::getWeight(OutputNode * node)
{
	int index = -1;
	for (unsigned i = 0; i < weights.size(); i++)
	{
		if (node == outputNodes[i]) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		DEBUG("ERROR");
	}

	return weights[index];
}

double HiddenNode::getError()
{
	return error;
}

double HiddenNode::getValue()
{
	return value;
}

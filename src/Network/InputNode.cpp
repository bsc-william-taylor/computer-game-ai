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

#include "InputNode.h"
#include "HiddenNode.h"
InputNode::InputNode()
	: value(0.0)
{
}

InputNode::~InputNode()
{
}

void InputNode::feedForwardTo(HiddenNode * node)
{
	float f = 0;
	//do {
	f = static_cast <float>(rand()) / (static_cast <float> (RAND_MAX / 1.0));
	//} while (f < 0.0001);

	hiddenLayerNodes.push_back(node);
	hiddenWeights.push_back(f);
}

void InputNode::adjustWeight(HiddenNode * node, double learning, double error)
{
	double& weight = getWeight(node);
	weight = weight + (learning * error * value);
}

void InputNode::setValue(double v)
{
	value = v;
}

double& InputNode::getWeight(HiddenNode * node)
{
	int index = 0;
	for (unsigned i = 0; i < hiddenLayerNodes.size(); i++)
	{
		if (node == hiddenLayerNodes[i]) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		DEBUG("FUCKING ERROR");
	}

	return hiddenWeights[index];
}


double& InputNode::getValue()
{
	return value;
}

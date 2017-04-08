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

#include "OutputNode.h"
#include "InputNode.h"

OutputNode::OutputNode()
{
	errorRate = 0.0;
	value = 0.0;
}

OutputNode::~OutputNode()
{
}

void OutputNode::setActivationFunction(std::function<double(std::vector<HiddenNode *>, OutputNode *)> func)
{
	activationFunction = func;
}

void OutputNode::finish(std::vector<HiddenNode *>& hiddenLayer)
{
	value = activationFunction(hiddenLayer, this);
}

void OutputNode::calculateError(double target)
{
	errorRate = target - value;
}

double OutputNode::getValue()
{
	return value;
}

double OutputNode::getError()
{
	return errorRate; 
}

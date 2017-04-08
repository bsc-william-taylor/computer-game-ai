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

#include "FunctionNode.h"

FunctionNode::FunctionNode(std::function<double(double, double)> func)
{
	spaceFunc = func;
	weight = 1.0;
}

FunctionNode::~FunctionNode()
{
}

void FunctionNode::activate(double d)
{
	value = spaceFunc(d, center);
}

void FunctionNode::adjustWeights(double learningRate, double error)
{
	weight += learningRate * error * value;
}

void FunctionNode::feedForward(ResultNode * node)
{
	node->appendValue(value * weight);
}

void FunctionNode::setCenter(double c)
{
	center = c;
}

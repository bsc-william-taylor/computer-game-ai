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
#include "ResultNode.h"

class FunctionNode
{
private:
	std::function<double(double, double)> spaceFunc;
public:
	FunctionNode(std::function<double(double, double)>);
	~FunctionNode();

	void adjustWeights(double learningRate, double error);
	void feedForward(ResultNode * node);
	void activate(double);
	void setCenter(double);

	double getCenter() {
		return center;
	}
private:
	double center;
	double weight;
	double value;
};

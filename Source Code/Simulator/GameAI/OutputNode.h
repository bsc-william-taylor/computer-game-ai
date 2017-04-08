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

class InputNode;
class HiddenNode;

class OutputNode
{
private:
	std::function<double(std::vector<HiddenNode *>&, OutputNode *)> activationFunction;
	double errorRate;
	double value;
public:
	OutputNode();
	~OutputNode();

	void setActivationFunction(std::function<double(std::vector<HiddenNode *>, OutputNode *)>);
	void calculateError(double target);

	void finish(std::vector<HiddenNode *>&);
	
	double getError();
	double getValue();
};

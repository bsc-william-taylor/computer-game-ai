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

class HiddenNode;
class OutputNode;

class InputNode 
{
private:
	std::vector<HiddenNode *> hiddenLayerNodes;
	std::vector<double> hiddenWeights;
	
	double value;
public:
	InputNode();
	~InputNode();

	void adjustWeight(HiddenNode *, double learning, double error);
	void feedForwardTo(HiddenNode *);
	void setWeight(double);
	void setValue(double);

	double& getWeight(HiddenNode *);
	double& getValue();
};

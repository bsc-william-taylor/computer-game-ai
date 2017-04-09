
#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <vector>
#include <time.h>
#include <math.h>
#include <assert.h>

#include "../../lib/freeglut/include/freeglut.h"
#include "test-parameters.h"
#include "timer.h"

template<typename T>
std::vector<T*> copy_vector(std::vector<std::unique_ptr<T>>& pointers)
{
    std::vector<T*> copies(pointers.size());
    for (auto i = 0; i < pointers.size(); ++i)
        copies[i] = pointers[i].get();
    return copies;
}

class TestParameters;
class Display;
class Graph;

// Our test class just creates and tests objects
class NeuralNetworkTest
{
private:
	// The paramers for the test
	TestParameters params;
	// The display we will render to
	Display * display;
	// The graph for the continuous function
	Graph* graph;
public:
	// Constructor & Deconstructor
	NeuralNetworkTest();
	~NeuralNetworkTest();

	// Sets up and creates a display using freeglut
	void setup(int argc, char ** argv);
	// Starts the main render loop showing test results
	void start();
private:
	// Sets up the continous function that we will be approximating
	void setupContinuousFunction();
	// Sets up the mlp that will be approimating it
	void setupMultiLayeredPercepton();
	// Sets up the rbf that will be approimating it
	void setupRadialBasisFunction();
};

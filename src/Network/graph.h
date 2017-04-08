
#pragma once

#include "neural-network.h"
#include "Common.h"

// A vector stucture for a 3d point
struct Point {
	double x;
	double y;
	double z;

	// A simple overloaded set function to ease interaction
	void set(double x, double y, double z) {
		this->x = x; this->y = y; this->z = z;
	}

	// Overloaded 2d version for 2d points
	void set(double x, double y) {
		this->x = x; this->y = y; this->z = 0;
	}
};

// Some typedefs to improve the readability of the code
typedef std::vector<Point>& TrainingSet;
typedef std::vector<Point> TrainingData;

// A graph object which draws the function on a display
class Graph
{
private:
	// The function f(x) that we will be drawing on the display
	std::function<double(double)> fx;
	// The functions distortion values
	std::vector<double> noiseValues;
	// The list of samples of the line (for nerual networks)
	std::vector<Point> graphSamples;
	// The colour of the line drawn by f(x)
	Point colour;
public:
	// Constructor & Deconstructor
	Graph(std::function<double(double)> fx);
	Graph(ArtificalNeuralNetwork * network);
	~Graph();

	// Returns the neural network being use to plot the graph
	ArtificalNeuralNetwork * getNetwork();
	// Returns a vector of training samples equal to sz
	TrainingData getTrainingSet(int sz);
	// Sets the function f(x)
	Graph * setFunction(std::function<double(double)>);
	// Sets the function f(x) by inputing x values in the nerual network
	Graph * setFunction(ArtificalNeuralNetwork * network);
	// Sets the colour of the graphs line
	Graph * setColour(double, double, double);
	// Applys distortion to the function where m is magnitude
	Graph * applyNoise(double m);
	// Draws the graph with OpenGL 2.0
	Graph * view();
private:
	// The network that will output a y value as f(x)
	ArtificalNeuralNetwork * neurelNetwork;
};
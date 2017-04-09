
#pragma once

#include "neural-network.h"
#include "main.h"

struct Point {
    double x, y, z;
    Point(double x = 0.0, double y = 0.0, double z = 0.0) {
        this->x = x; 
        this->y = y; 
        this->z = z;
    }
};

using TrainingData = std::vector<Point>;

class Graph
{
    std::function<double(double)> fx;
    std::vector<double> noiseValues;
    std::vector<Point> graphSamples;
    NeuralNetwork * neurelNetwork;
    Point colour;
public:
    Graph(std::function<double(double)> fx);
    Graph(NeuralNetwork* network);
    ~Graph();

    NeuralNetwork* getNetwork();

    Graph* setFunction(std::function<double(double)>);
    Graph* setFunction(NeuralNetwork * network);
    Graph* setColour(double, double, double);
    Graph* applyNoise(double m);
    Graph* view();

    TrainingData getTrainingSet(int sz);
};
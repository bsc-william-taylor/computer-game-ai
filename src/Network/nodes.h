
#pragma once

#include "main.h"

class ResultNode;
class HiddenNode;
class InputNode;
class FunctionNode;
class OutputNode;

using HiddenLayerMLP = std::vector<std::unique_ptr<HiddenNode>>;
using OutputLayer = std::vector<std::unique_ptr<OutputNode>>;
using InputLayer = std::vector<std::unique_ptr<InputNode>>;

using HiddenLayerRBF = std::vector<std::unique_ptr<FunctionNode>>;
using SpaceFunc = std::function<double(double, double)>;

class FunctionNode
{
private:
    std::function<double(double, double)> spaceFunc;
public:
    FunctionNode(std::function<double(double, double)>);
    ~FunctionNode();

    void adjustWeights(double learningRate, double error);
    void feedForward(ResultNode* node);
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

class ReceptorNode 
{
    FunctionNode* channel;
    double value;
public:
    ReceptorNode();
    ~ReceptorNode();

    void feedForward(FunctionNode* functions);
    void setValue(double);
};

class ResultNode 
{
    double output;
public:
    ResultNode();
    ~ResultNode();

    double getError(double t);
    double getValue();

    void appendValue(double);
};

class InputNode
{
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

class HiddenNode
{
    std::function<double(std::vector<InputNode *>&, HiddenNode *)> activationFunction;
    std::vector<OutputNode *> outputNodes;
    std::vector<double> weights;

    bool bias;
    double error;
    double value;
public:
    HiddenNode();
    ~HiddenNode();

    std::function<double(std::vector<InputNode *>&, HiddenNode *)> getFunction() {
        return activationFunction;
    }

    void setActivationFunction(std::function<double(std::vector<InputNode *>, HiddenNode *)>);
    void feedForwardTo(OutputNode *);
    void feedForward(std::vector<InputNode *>&);

    void calculateError(OutputNode * node, double outputError);
    void adjustWeight(OutputNode * node, double learning, double error);
    void setValue(double);
    void makeBias() {
        bias = true;
        value = 1.0;
    }

    bool isBias() {
        return bias;
    }

    double getError();
    double& getWeight(OutputNode * node);
    double getValue();
};

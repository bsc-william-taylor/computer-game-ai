
#include "Nodes.h"

ResultNode::ResultNode()
{
    output = 0.0;
}

ResultNode::~ResultNode()
{

}

void ResultNode::appendValue(double v)
{
    output += v;
}

double ResultNode::getValue()
{
    double copy = output;
    output = 0.0;
    return copy;
}

double ResultNode::getError(double t)
{
    return (t - getValue());
}

ReceptorNode::ReceptorNode()
{
    channel = NULL;
}

ReceptorNode::~ReceptorNode()
{

}

void ReceptorNode::setValue(double v)
{
    value = v;
}

void ReceptorNode::feedForward(FunctionNode * function)
{
    function->activate(value);
}

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


InputNode::InputNode()
    : value(0.0)
{
}

InputNode::~InputNode()
{
}

void InputNode::feedForwardTo(HiddenNode * node)
{
    float f = static_cast <float>(rand()) / (static_cast <float> (RAND_MAX / 1.0));
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

    assert(index != -1);
    return hiddenWeights[index];
}


double& InputNode::getValue()
{
    return value;
}

HiddenNode::HiddenNode() : 
    value(0.0)
{
    bias = false;
}

HiddenNode::~HiddenNode()
{
}

void HiddenNode::setActivationFunction(std::function<double(std::vector<InputNode *>, HiddenNode *)> a)
{
    this->activationFunction = a;
}

void HiddenNode::feedForwardTo(OutputNode * node)
{
    auto f = static_cast <float>(rand()) / (static_cast <float> (RAND_MAX / 1.0));
    outputNodes.push_back(node);
    weights.push_back(f);
}

void HiddenNode::setValue(double v)
{
    this->value = v;
}

void HiddenNode::feedForward(std::vector<InputNode *>& inputs)
{
    value = (activationFunction(inputs, this));
}

void HiddenNode::calculateError(OutputNode * node, double outputError)
{
    error = outputError * getWeight(node) * value * (1 - value);
}

void HiddenNode::adjustWeight(OutputNode * node, double learning, double totalError)
{
    double& weight = getWeight(node);
    weight = weight + (learning * totalError * value);
}

double& HiddenNode::getWeight(OutputNode * node)
{
    int index = -1;
    for (unsigned i = 0; i < weights.size(); i++)
    {
        if (node == outputNodes[i]) {
            index = i;
            break;
        }
    }

    assert(index != -1);
    return weights[index];
}

double HiddenNode::getError()
{
    return error;
}

double HiddenNode::getValue()
{
    return value;
}

FunctionNode::FunctionNode(std::function<double(double, double)> func) :
    spaceFunc(func),
    weight(1.0)
{
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

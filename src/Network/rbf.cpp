
#include "rbf.h"

RBF::RBF() :
    errorThreshold(0.01),
    learningRate(0.2)
{
}

RBF::~RBF()
{
}

RBF* RBF::setErrorThreshold(double error)
{
    errorThreshold = error;
    return this;
}

RBF* RBF::setLearningRate(double rate)
{
    learningRate = rate;
    return this;
}

RBF* RBF::setTrainingData(TrainingData set)
{
    trainingSet = set;
    return this;
}

RBF* RBF::setSpaceFunction(SpaceFunc func)
{
    spaceFunc = func;
    return this;
}

RBF* RBF::setupHiddenLayer()
{
    for (auto i = 0; i < trainingSet.size(); i++)
    {
        auto node = std::make_unique<FunctionNode>(spaceFunc);
        node->setCenter(trainingSet[i].x);
        hiddenLayer.push_back(std::move(node));
    }

    return this;
}

double RBF::fx(double x)
{
    inputLayer.setValue(x);

    for (auto& hiddenNeuron : hiddenLayer)
    {
        inputLayer.feedForward(hiddenNeuron.get());
        hiddenNeuron->feedForward(&outputLayer);
    }

    return outputLayer.getValue();
}


RBF* RBF::train(int iterations)
{
    for (auto i = 0; i < iterations;)
    {
        auto trains = 0u;

        while (trains < trainingSet.size())
        {
            auto& point = trainingSet[trains];
            inputLayer.setValue(point.x);
            i++;

            for (auto& hiddenNeuron : hiddenLayer)
            {
                inputLayer.feedForward(hiddenNeuron.get());
                hiddenNeuron->feedForward(&outputLayer);
            }

            double error = outputLayer.getError(point.y);
            trains += abs(error) <= errorThreshold ? 1 : 0;

            for (auto& hiddenNeuron : hiddenLayer)
            {
                hiddenNeuron->adjustWeights(learningRate, error);
            }
        }
    }

    return this;
}


#include "mlp.h"

MLP::MLP() :
    errorThreshold(0.1),
    learningRate(0.1)
{
}

MLP::~MLP()
{
}

MLP* MLP::setErrorThreshold(double err)
{
    errorThreshold = err;
    return this;
}

MLP* MLP::setLearningRate(double rate)
{
    learningRate = rate;
    return this;
}

MLP* MLP::setOutputLayer(OutputLayer vec)
{
    outputNeurons = std::move(vec);
    return this;
}

MLP* MLP::setHiddenLayer(HiddenLayerMLP vec)
{
    hiddenNeurons = std::move(vec);

    auto bias = std::make_unique<HiddenNode>();
    bias->setActivationFunction(hiddenNeurons[0]->getFunction());
    bias->makeBias();

    for (auto i = 0; i < outputNeurons.size(); i++)
    {
        bias->feedForwardTo(outputNeurons[i].get());
    }

    hiddenNeurons.push_back(std::move(bias));
    return this;
}

MLP* MLP::setInputLayer(InputLayer vec)
{
    inputNeurons = std::move(vec);
    auto bias = std::make_unique<InputNode>();
    bias->setValue(1.0);

    for (unsigned i = 0; i < hiddenNeurons.size(); i++) 
    {
        if (hiddenNeurons[i]->getValue() == 0.0) 
        {
            bias->feedForwardTo(hiddenNeurons[i].get());
        }
    }

    inputNeurons.push_back(std::move(bias));
    return this;
}

MLP* MLP::train(int iterations)
{
    std::vector<bool> testsCompleted(trainingSet.size(), { false });
    auto testID = chooseInputPattern(NULL, testsCompleted);
    auto times = 0;

    while (times <= iterations)
    {
        auto& test = trainingSet[testID];
        inputNeurons[0]->setValue(test.x);

        for (auto& hiddenNode : hiddenNeurons)
        {
            hiddenNode->feedForward(copy_vector(inputNeurons));
        }

        outputNeurons[0]->finish(copy_vector(hiddenNeurons));
        double error = test.y - outputNeurons[0]->getValue();

        if (abs(error) <= errorThreshold) 
        {            
            testsCompleted[testID] = true;
            auto totalTests = 0;
            ++times;

            for (auto& v : testsCompleted)
                if (v) 
                    totalTests++;

            if (totalTests == testsCompleted.size())
            { 
                break;
            }

            testID = chooseInputPattern(testID, testsCompleted);
        }
        else
        {
            std::fill(testsCompleted.begin(), testsCompleted.end(), false);

            for (auto & neuron : hiddenNeurons)
            {
                if (!neuron->isBias())
                {
                    neuron->calculateError(outputNeurons[0].get(), error);
                }

                neuron->adjustWeight(outputNeurons[0].get(), learningRate, error);
            }

            for (auto& inputNeuron : inputNeurons)
            {
                for (auto& hiddenNeuron : hiddenNeurons)
                {
                    if (!hiddenNeuron->isBias())
                    {
                        inputNeuron->adjustWeight(hiddenNeuron.get(), learningRate, hiddenNeuron->getError());
                    }
                }
            }

            testID = chooseInputPattern(testID, testsCompleted);
        }
    }

    return this;
}

int MLP::chooseInputPattern(int TEST_ID, std::vector<bool>& vec)
{
    int ID = TEST_ID;
    int testID = 0;
    do {
        testID = rand() % trainingSet.size();
    } while (ID == testID && vec[testID]);

    return testID;
}

MLP* MLP::setTrainingSet(TrainingData point)
{
    trainingSet = point;
    return this;
}

double MLP::fx(double x)
{
    inputNeurons.front()->setValue(x);

    for (auto& hiddenNode : hiddenNeurons)
    {
        hiddenNode->feedForward(copy_vector(inputNeurons));
    }

    outputNeurons.front()->finish(copy_vector(hiddenNeurons));
    return outputNeurons.front()->getValue();
}

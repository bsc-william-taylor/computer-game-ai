
#include "mlp.h"

MLP::MLP() : 
    errorThreshold(0.1), 
    learningRate(0.1)
{
}

MLP::~MLP()
{
}

MLP * MLP::setErrorThreshold(double err)
{
    errorThreshold = err;
    return this;
}

MLP * MLP::setLearningRate(double rate)
{
    learningRate = rate;
    return this;
}

MLP * MLP::setOutputLayer(OutputLayer vec)
{
    outputNeurons = std::move(vec);
    return this;
}

MLP * MLP::setHiddenLayer(HiddenLayerMLP vec)
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

MLP * MLP::setInputLayer(InputLayer vec)
{
    inputNeurons = std::move(vec);

    auto bias = std::make_unique<InputNode>();
    bias->setValue(1.0);
    for (unsigned i = 0; i < hiddenNeurons.size(); i++) {
        if (hiddenNeurons[i]->getValue() == 0.0) {
            bias->feedForwardTo(hiddenNeurons[i].get());
        }
    }

    inputNeurons.push_back(std::move(bias));
    return this;
}

MLP * MLP::train(int iterations)
{
    std::vector<bool> testsCompleted;
    testsCompleted.resize(trainingSet.size());
    for (auto& v : testsCompleted) {
        v = false;
    }

    int testID = chooseInputPattern(NULL, testsCompleted);

    int actualTimes = 0;
    while (actualTimes <= iterations) {
        Point& test = trainingSet[testID];
        inputNeurons[0]->setValue(test.x);

        for (auto& hiddenNode : hiddenNeurons) 
        {
            hiddenNode->feedForward(copy_vector(inputNeurons));
        }

        outputNeurons[0]->finish(copy_vector(hiddenNeurons));

        double error = test.y - outputNeurons[0]->getValue();

        if (abs(error) <= errorThreshold) {
            ++actualTimes;
            testsCompleted[testID] = true;
            int totalTests = 0;
            for (auto& v : testsCompleted) {
                if (v) totalTests++;
            }

            if (totalTests == testsCompleted.size()) {
                break;
            }
            else {
                testID = chooseInputPattern(testID, testsCompleted);
            }
        }
        else {
            for (auto& v : testsCompleted) { v = false; }

            // Adjust weights in the hidden neuron
            for (auto & neuron : hiddenNeurons) {
                if (!neuron->isBias()) {
                    neuron->calculateError(outputNeurons[0].get(), error);
                }

                neuron->adjustWeight(outputNeurons[0].get(), learningRate, error);
            }

            for (auto & neuron : inputNeurons) {
                for (int i = 0; i < hiddenNeurons.size(); i++) {
                    if (!hiddenNeurons[i]->isBias()) {
                        neuron->adjustWeight(hiddenNeurons[i].get(), learningRate, hiddenNeurons[i]->getError());
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

MLP * MLP::setTrainingSet(TrainingData point)
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

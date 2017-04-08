
#include "main.h"
#include "Nodes.h"
#include "mlp.h"
#include "rbf.h"

NeuralNetworkTest::NeuralNetworkTest()
{
    display = Display::create(720, 480);
}

NeuralNetworkTest::~NeuralNetworkTest()
{
}

void NeuralNetworkTest::setup(int argc, char ** argv)
{
    display->setup(argc, argv);
}

void NeuralNetworkTest::start()
{
    setupContinuousFunction();
    setupMultiLayeredPercepton();
    setupRadialBasisFunction();

    display->show("GameAI Graphs : Blue = RBF, Green = MLP, Red = Function, Gray = Noise");
}

void NeuralNetworkTest::setupContinuousFunction() {
    auto noiseGraph = std::make_unique<Graph>([](double x) { return (sin(x) / 1.5); });
    noiseGraph->setColour(0.6, 0.6, 0.6);
    noiseGraph->applyNoise(conditions.NOISE);
    graph = noiseGraph.get();

    auto normalGraph = std::make_unique<Graph>([](double x) { return (sin(x) / 1.5); });
    normalGraph->setColour(1.0, 0.0, 0.0);

    graph = noiseGraph.get();
    display->installGraph(std::move(normalGraph));
    display->installGraph(std::move(noiseGraph));
}

void NeuralNetworkTest::setupMultiLayeredPercepton()
{
    HiddenLayerMLP hiddenLayer(6);
    OutputLayer outputLayer(1);
    InputLayer inputLayer(1);

    using HiddenFunction = std::function<double(std::vector<InputNode *>&, HiddenNode *)>;
    HiddenFunction hiddenFunc = [](std::vector<InputNode *>& inputs, HiddenNode * node) {
        double output = 0.0;
        for (auto& input : inputs)
            output += input->getValue() * input->getWeight(node);
        return 1.0 / (1.0 + exp(-output));
    };

    using OutputFunction = std::function<double(std::vector<HiddenNode *>&, OutputNode *)>;
    OutputFunction outputFunc = [](std::vector<HiddenNode *>& nodes, OutputNode * node) {
        double output = 0.0;
        for (auto& hidden : nodes)
            output += (hidden->getValue() * hidden->getWeight(node));
        return(output);
    };

    outputLayer[0] = std::make_unique<OutputNode>();
    outputLayer[0]->setActivationFunction(outputFunc);
    inputLayer[0] = std::make_unique<InputNode>();

    for (auto& hiddenNode : hiddenLayer)
    {
        hiddenNode = std::make_unique<HiddenNode>();
        hiddenNode->setActivationFunction(hiddenFunc);
        hiddenNode->feedForwardTo(outputLayer.front().get());

        inputLayer[0]->feedForwardTo(hiddenNode.get());
    }

    auto trainingDataset = graph->getTrainingSet(conditions.TRAINING_SET);
    auto network = new MLP();
    network->setErrorThreshold(conditions.MLP_ERROR_THRESHOLD);
    network->setLearningRate(conditions.MLP_LEARNING_RATE);
    network->setTrainingSet(trainingDataset);
    network->setOutputLayer(std::move(outputLayer));
    network->setHiddenLayer(std::move(hiddenLayer));
    network->setInputLayer(std::move(inputLayer));
    network->train(conditions.MLP_ITERATIONS);

    auto graph = std::make_unique<Graph>(network);
    graph->setColour(0.0, 1.0, 0.0);
    display->installGraph(std::move(graph));
}

void NeuralNetworkTest::setupRadialBasisFunction()
{
    auto trainingSet = graph->getTrainingSet(conditions.TRAINING_SET);
    auto network = new RBF();
    network->setErrorThreshold(conditions.RBF_ERROR_THRESHOLD);
    network->setLearningRate(conditions.RBF_LEARNING_RATE);
    network->setSpaceFunction([](double x, double c) { return exp(-1.0 * pow(abs(x - c), 2.0)); });
    network->setTrainingData(trainingSet);
    network->setupHiddenLayer();
    network->train(conditions.RBF_ITERATIONS);

    auto graph = std::make_unique<Graph>(network);
    graph->setColour(0.0, 0.0, 1.0);
    display->installGraph(std::move(graph));
}

int WINAPI WinMain(HINSTANCE h, HINSTANCE p, LPSTR w, int c)
{
    NeuralNetworkTest neuralNetworkTest;
    neuralNetworkTest.setup(NULL, NULL);
    neuralNetworkTest.start();
    return EXIT_SUCCESS;
}
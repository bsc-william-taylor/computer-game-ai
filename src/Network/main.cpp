
#include "main.h"
#include "Nodes.h"
#include "mlp.h"
#include "rbf.h"

// Constructor & Deconstructor
NeuralNetworkTest::NeuralNetworkTest()
{
	// Creates our display object with a specific size
	display = Display::create(720, 480);
}

NeuralNetworkTest::~NeuralNetworkTest()
{
}

// This function sets up the display for the tests
void NeuralNetworkTest::setup(int argc, char ** argv)
{
	// providing a display was given to us
	if (display != nullptr)	{
		// set it up 
		display->setup(argc, argv);
	}
}

// This funciton just starts the tests
void NeuralNetworkTest::start()
{
	// We setup a continuous function & mlp, rbf networks
	setupContinuousFunction();
	setupMultiLayeredPercepton();
	setupRadialBasisFunction();

	// Now if we have a display we show the results
	if (display != nullptr)	{
		display->show("GameAI Graphs : Blue = RBF, Green = MLP, Red = Function, Gray = Noise");
	} else {
		MessageBox(NULL, "Error With Display!", "Error", MB_OK);
	}
}

// This function sets up a graph to show the continous function we are approximating
void NeuralNetworkTest::setupContinuousFunction() {
	// We create the graph or line we will be approximating
    auto noiseGraph = std::make_unique<Graph>([](double x) { return (sin(x) / 1.5); });
    noiseGraph->setColour(0.6, 0.6, 0.6);			// we then set the line colour on the graph
    noiseGraph->applyNoise(conditions.NOISE);	// we then also apply some noise to it as well
    graph = noiseGraph.get();

    auto normalGraph = std::make_unique<Graph>([](double x) { return (sin(x) / 1.5); });
    normalGraph->setColour(1.0, 0.0, 0.0);

    graph = noiseGraph.get();
	display->installGraph(std::move(normalGraph));
	display->installGraph(std::move(noiseGraph));
}

// This function sets up the multi layered percepton that will approximate the functoin
void NeuralNetworkTest::setupMultiLayeredPercepton() {
	// Fist we acquire a training set with TRAINING_SET number of samples
	auto trainingSet = graph->getTrainingSet(conditions.TRAINING_SET);
	// We then create the mlp and all its nodes to create the network
	auto perceptronNetwork = new MultiLayeredPercepton();
	auto hiddenNode1 = new HiddenNode();
	auto hiddenNode2 = new HiddenNode();
	auto hiddenNode3 = new HiddenNode();
	auto hiddenNode4 = new HiddenNode();
	auto hiddenNode5 = new HiddenNode();
	auto outputNode = new OutputNode();
	auto inputNode = new InputNode();

	// We create our activation function for the hidden layer
	std::function<double(std::vector<InputNode *>&, HiddenNode *)> hiddenFunc =
		([](std::vector<InputNode *>& inputs, HiddenNode * node) {
			double output = 0.0;

			for (auto& input : inputs) {
				output += (input->getValue() * input->getWeight(node));
			}

			return 1.0 / (1.0 + exp(-output));
		}
	);

	// We then create a linear activation function for the output
	std::function<double(std::vector<HiddenNode *>&, OutputNode *)> outputFunc =
		([](std::vector<HiddenNode *>& hiddenNeurons, OutputNode * node) {
			double output = 0.0;

			for (auto& hidden : hiddenNeurons) {
				output += (hidden->getValue() * hidden->getWeight(node));
			}

			return(output);
		}
	);

	// We then take those activation functions and give them to the nuerons
	hiddenNode1->setActivationFunction(hiddenFunc);
	hiddenNode2->setActivationFunction(hiddenFunc);
	hiddenNode3->setActivationFunction(hiddenFunc);
	hiddenNode4->setActivationFunction(hiddenFunc);
	hiddenNode5->setActivationFunction(hiddenFunc);

	outputNode->setActivationFunction(outputFunc);

	// We then show the neurons where they feed forward to
	hiddenNode1->feedForwardTo(outputNode);
	hiddenNode2->feedForwardTo(outputNode);
	hiddenNode3->feedForwardTo(outputNode);
	hiddenNode4->feedForwardTo(outputNode);
	hiddenNode5->feedForwardTo(outputNode);
	
	inputNode->feedForwardTo(hiddenNode1);
	inputNode->feedForwardTo(hiddenNode2);
	inputNode->feedForwardTo(hiddenNode3);
	inputNode->feedForwardTo(hiddenNode4);
	inputNode->feedForwardTo(hiddenNode5);

	// We then set the multi layered perceptron properties
	perceptronNetwork->setErrorThreshold(conditions.MLP_ERROR_THRESHOLD);
	perceptronNetwork->setLearningRate(conditions.MLP_LEARNING_RATE);
	perceptronNetwork->setTrainingSet(trainingSet);
	perceptronNetwork->setOutputLayer({ outputNode });
	perceptronNetwork->setHiddenLayer({ hiddenNode1, hiddenNode2, hiddenNode3, hiddenNode4, hiddenNode5 });
	perceptronNetwork->setInputLayer({ inputNode });

	// start the timer
	Timer::start();

	// after which we then train the network 
	perceptronNetwork->train(conditions.MLP_ITERATIONS);

	// print the train time to the console
	std::cout << "MLP : " << (Timer::stop()) << std::endl;

    auto mlpGraph = std::make_unique<Graph>(perceptronNetwork);
    mlpGraph->setColour(0.0, 1.0, 0.0);

	// and then install it to the display so it can be displayed
	display->installGraph(std::move(mlpGraph));
}

// This function sets up the radial basis function which will approximate the function
void NeuralNetworkTest::setupRadialBasisFunction() {
	// We create the network object first
	auto network = new RadicalBasisFunction();
	// The acquire a data set in which to train the network with
	auto trainingSet = graph->getTrainingSet(conditions.TRAINING_SET);

	// We then set the RBF function which will convert values to RBF space
	std::function<double(double, double)> spaceFunction = (
		[](double x, double c) {
			static const double bias = -1.0;
			return exp(bias * pow(abs(x - c), 2.0));
		}
	);

	// We then set some parameters for the network
	network->setErrorThreshold(conditions.RBF_ERROR_THRESHOLD);
	network->setLearningRate(conditions.RBF_LEARNING_RATE);
	network->setSpaceFunction(spaceFunction);
	network->setTrainingData(trainingSet);
	network->setupHiddenLayer();

	// start the timer
	Timer::start();

	// then we train it
	network->train(conditions.RBF_ITERATIONS);

	// print out the train time
	std::cout << "RBF : " << (Timer::stop()) << std::endl;

    auto rbfGraph = std::make_unique<Graph>(network);
    rbfGraph->setColour(0.0, 0.0, 1.0);
	display->installGraph(std::move(rbfGraph));
}

// Entry Point
int WINAPI WinMain(HINSTANCE h, HINSTANCE p, LPSTR w, int c) {
	// Very little here we just create the test object and start it
	NeuralNetworkTest neuralNetworkTest;
	neuralNetworkTest.setup(NULL, NULL);
	neuralNetworkTest.start();
	// then return 0 to the main function
	return EXIT_SUCCESS;
}
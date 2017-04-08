
#include "mlp.h"

MultiLayeredPercepton::MultiLayeredPercepton()
	: errorThreshold(0.1), learningRate(0.1)
{
}

MultiLayeredPercepton::~MultiLayeredPercepton()
{
	for (auto& i : inputNeurons) {
		delete i;
	}

	for (auto& i : hiddenNeurons) {
		delete i;
	}

	for (auto& i : outputNeurons) {
		delete i;
	}
}

MultiLayeredPercepton * MultiLayeredPercepton::setErrorThreshold(double err)
{
	errorThreshold = err;
	return this;
}

MultiLayeredPercepton * MultiLayeredPercepton::setLearningRate(double rate)
{
	learningRate = rate;
	return this;
}

MultiLayeredPercepton * MultiLayeredPercepton::setOutputLayer(std::vector<OutputNode *> vec)
{
	outputNeurons = std::vector<OutputNode *>(vec);
	return this;
}

MultiLayeredPercepton * MultiLayeredPercepton::setHiddenLayer(std::vector<HiddenNode *> vec)
{
	hiddenNeurons = std::vector<HiddenNode *>(vec);
	HiddenNode * bias = new HiddenNode();
	bias->setActivationFunction(hiddenNeurons[0]->getFunction());
	bias->makeBias();
	
	for (unsigned i = 0; i < outputNeurons.size(); i++){
		bias->feedForwardTo(outputNeurons[i]);
	}

	hiddenNeurons.push_back(bias);
	return this;
}

MultiLayeredPercepton * MultiLayeredPercepton::setInputLayer(std::vector<InputNode *> vec)
{
	inputNeurons = std::vector<InputNode *>(vec);
	InputNode * bias = new InputNode();
	bias->setValue(1.0);
	for (unsigned i = 0; i < hiddenNeurons.size(); i++){
		if (hiddenNeurons[i]->getValue() == 0.0) {
			bias->feedForwardTo(hiddenNeurons[i]);
		}
	}

	inputNeurons.push_back(bias);
	return this;
}

MultiLayeredPercepton * MultiLayeredPercepton::train(int iterations)
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

		for (auto& hiddenNode : hiddenNeurons) {
			hiddenNode->feedForward(inputNeurons);
		}

		outputNeurons[0]->finish(hiddenNeurons);
		
		double error = test.y - outputNeurons[0]->getValue();

//		DEBUG(error);

		if (abs(error) <= errorThreshold) {
			++actualTimes;
			testsCompleted[testID] = true;
			int totalTests = 0;
			for (auto& v : testsCompleted) {
				if (v) totalTests++;
			}

			if (totalTests == testsCompleted.size()){
				break;
			} else {
				testID = chooseInputPattern(testID, testsCompleted); 
			}
		} else {
			for (auto& v : testsCompleted) { v = false; }
			
			// Adjust weights in the hidden neuron
			for (auto & neuron : hiddenNeurons) {
				if (!neuron->isBias()) {
					neuron->calculateError(outputNeurons[0], error);
				}

				neuron->adjustWeight(outputNeurons[0], learningRate, error);
			}

			for (auto & neuron : inputNeurons) {
				for (int i = 0; i < hiddenNeurons.size(); i++) {
					if (!hiddenNeurons[i]->isBias()) {
						neuron->adjustWeight(hiddenNeurons[i], learningRate, hiddenNeurons[i]->getError());
					}
				}
			}

			//std::cout << "End" << std::endl;

			testID = chooseInputPattern(testID, testsCompleted);
		}
	}

	//std::cout << actualTimes << std::endl;
	return this;
}

int MultiLayeredPercepton::chooseInputPattern(int TEST_ID, std::vector<bool>& vec)
{
	int ID = TEST_ID;
	int testID = 0;
	do  {
		testID = rand() % trainingSet.size();
	} while (ID == testID && vec[testID]);

	return testID;
}

MultiLayeredPercepton * MultiLayeredPercepton::setTrainingSet(std::vector<Point> point)
{
	this->trainingSet = point;

	return this;
}

double MultiLayeredPercepton::fx(double x)
{
	inputNeurons[0]->setValue(x);

	for (auto& hiddenNode : hiddenNeurons) {
		hiddenNode->feedForward(inputNeurons);
	}

	outputNeurons[0]->finish(hiddenNeurons);
	return outputNeurons[0]->getValue();
}

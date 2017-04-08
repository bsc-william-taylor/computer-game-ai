
#pragma once

#include "tinyxml2.h"
#include "Display.h"
#include "Graph.h"

using namespace tinyxml2;

struct TestParameters {
	unsigned int MLP_ITERATIONS;
	unsigned int RBF_ITERATIONS;

	double MLP_ERROR_THRESHOLD;
	double RBF_ERROR_THRESHOLD;
	double MLP_LEARNING_RATE;
	double RBF_LEARNING_RATE;

	unsigned int TRAINING_SET = 10;
	double NOISE = 0.075;

	TestParameters() {
		XMLDocument settingsDocument;
		settingsDocument.LoadFile("settings.xml");

		XMLNode * root = settingsDocument.FirstChildElement("Settings")->FirstChildElement("SettingsMLP");

		MLP_ERROR_THRESHOLD = atof(root->FirstChildElement("ErrorThreshold")->GetText());
		MLP_LEARNING_RATE = atof(root->FirstChildElement("LearningRate")->GetText());
		MLP_ITERATIONS = atof(root->FirstChildElement("Iterations")->GetText());
		
		root = settingsDocument.FirstChildElement("Settings")->FirstChildElement("SettingsRBF");

		RBF_ERROR_THRESHOLD = atof(root->FirstChildElement("ErrorThreshold")->GetText());
		RBF_LEARNING_RATE = atof(root->FirstChildElement("LearningRate")->GetText());
		RBF_ITERATIONS = atof(root->FirstChildElement("Iterations")->GetText());
		
		TRAINING_SET = atof(settingsDocument.FirstChildElement("Settings")->FirstChildElement("TrainingSet")->GetText());
		NOISE =  atof(settingsDocument.FirstChildElement("Settings")->FirstChildElement("Noise")->GetText());
	}
};

// Our test class just creates and tests objects
class NeuralNetworkTest
{
private:
	// The paramers for the test
	TestParameters conditions;
	// The display we will render to
	Display * display;
	// The graph for the continuous function
	Graph * graph;
public:
	// Constructor & Deconstructor
	NeuralNetworkTest();
	~NeuralNetworkTest();

	// Sets up and creates a display using freeglut
	void setup(int argc, char ** argv);
	// Starts the main render loop showing test results
	void start();
private:
	// Sets up the continous function that we will be approximating
	void setupContinuousFunction();
	// Sets up the mlp that will be approimating it
	void setupMultiLayeredPercepton();
	// Sets up the rbf that will be approimating it
	void setupRadialBasisFunction();
};

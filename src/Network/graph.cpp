
#include "Graph.h"

Graph::Graph(NeuralNetwork * neturalNetwork)
{
    neurelNetwork = neturalNetwork;
    colour = Point(1.0, 0.0, 0.0);
    fx = [](double x) { return x; };
}

Graph::Graph(std::function<double(double)> func)
{
    colour = Point(1.0, 0.0, 0.0);
    neurelNetwork = NULL;
    fx = func;
}

Graph::~Graph()
{
    if (neurelNetwork != NULL) {
        delete neurelNetwork;
    }
}

Graph * Graph::setColour(double r, double g, double b)
{
    colour = Point(r, g, b);
    return this;
}

Graph * Graph::setFunction(std::function<double(double)> func)
{
    fx = func;
    return this;
}

Graph * Graph::view()
{
    // We start by specifing the drawing type
    glBegin(GL_LINE_STRIP);
    // The we get the vertices colour
    glColor3d(colour.x, colour.y, colour.z);
    // Now if we dont have a nerual network
    if (neurelNetwork == NULL) {
        // we check to see if we have noise values before we call fx()
        if (noiseValues.empty()) {
            // if we dont we render the vertices without noise being added
            for (double x = 0.0; x < 6.28318530718; x += (6.28318530718 / 180.0f)) {
                glVertex2d(x, fx(x));
            }
        }
        else {
            // if we do have noise add the noise onto y
            int i = 0;
            for (double x = 0.0; x < 6.28318530718; x += (6.28318530718 / 180.0f)) {
                glVertex2d(x, fx(x) + noiseValues[i++]);
            }
        }
    }
    else {
        // if we do have a nerual network we set the value of the input node and draw the output
        for (double x = 0.0; x < 6.28318530718; x += (6.28318530718 / 180.0f)) {
            glVertex2d(x, neurelNetwork->fx(x));
        }
    }

    // End the current drawing phase
    glEnd();

    // Begin a new drawing phase 
    glBegin(GL_POINTS);
    glColor3d(1.0, 0.7, 0.0);	// set the colour of each point to ORANGE

    // The draw all the graph samples for debugging reasons
    for (auto& point : graphSamples) {
        glVertex2d(point.x, point.y);
    }

    // End the current drawing phase
    glEnd();
    // Then return the current instance
    return this;
}

// Here we return a set of data samples for training nerual networks
TrainingData Graph::getTrainingSet(int sz)
{
    // if we have entered a new size of if samples is empty
    if (sz != graphSamples.size()) {
        // cast to a double value for use in the for loop
        double s = static_cast<double>(sz);

        // Then keep track of insertions
        int ID = 0;
        // Then create sample values based on the sz value
        for (double x = 0.0; x < 6.28318530718; x += (6.28318530718 / s)) {
            // Create a sample point
            Point p;
            p.x = x;
            // Check to see if we should add noise to the sample
            noiseValues.size() > 0 ? p.y = fx(x) + noiseValues[ID] : p.y = fx(x);
            // push it into the sample list
            graphSamples.push_back(p);
            // Then go to the next point in the vector
            ID += (int)floor((180.0 / s));
        }
    }

    // returns a copy of the vector for training the nerual network
    return graphSamples;
}

// This function applys noise by creating a list of noise values when the graph is plotted
Graph * Graph::applyNoise(double noiseMag)
{
    // Here we just generate a list of noise values
    for (double x = 0.0; x < 6.28318530718; x += (6.28318530718 / 180.0f)) {
        // create a random noise value.
        double noise = ((rand() % 201) - 100.0) / 100.0;
        noiseValues.push_back((noise * noiseMag));	// & multiply them by noise magnitude
    }

    return this;
}

// Just a get function for the nerual network being used
NeuralNetwork * Graph::getNetwork()
{
    return neurelNetwork;
}

// Sets the neural network we will be using instead of a function object
Graph * Graph::setFunction(NeuralNetwork * network)
{
    neurelNetwork = network;
    return this;
}

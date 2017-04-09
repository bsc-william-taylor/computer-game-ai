
#pragma once

#include "tinyxml2.h"

using namespace tinyxml2;

class TestParameters
{
public:
    struct
    {
        int iterations;
        double errorThreshold;
        double learningRate;
    } mlp, rbf;

    double noise = 0.075;
    int trainingSet = 10;

    TestParameters(const char* filename);
    XMLElement* getRootNode(XMLDocument&, const char*, const char*);
    const char* getNodeText(XMLDocument&, const char*, const char*);
};

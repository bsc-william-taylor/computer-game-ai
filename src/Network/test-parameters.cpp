
#include "test-parameters.h"

TestParameters::TestParameters(const char* filename) 
{
    XMLDocument document;
    document.LoadFile(filename);

    auto rootOne = getRootNode(document, "Settings", "SettingsMLP");
    auto rootTwo = getRootNode(document, "Settings", "SettingsRBF");

    mlp.errorThreshold = atof(rootOne->FirstChildElement("ErrorThreshold")->GetText());
    mlp.learningRate = atof(rootOne->FirstChildElement("LearningRate")->GetText());
    mlp.iterations = atof(rootOne->FirstChildElement("Iterations")->GetText());

    rbf.errorThreshold = atof(rootTwo->FirstChildElement("ErrorThreshold")->GetText());
    rbf.learningRate = atof(rootTwo->FirstChildElement("LearningRate")->GetText());
    rbf.iterations = atof(rootTwo->FirstChildElement("Iterations")->GetText());

    trainingSet = atof(getNodeText(document, "Settings", "TrainingData"));
    noise = atof(getNodeText(document, "Settings", "Noise"));
}

XMLElement* TestParameters::getRootNode(XMLDocument& doc, const char* base, const char* section)
{
    return doc.FirstChildElement(base)->FirstChildElement(section);
}

const char* TestParameters::getNodeText(XMLDocument& doc, const char* base, const char* section)
{
    return getRootNode(doc, base, section)->GetText();
}
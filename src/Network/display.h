
#pragma once

#include "graph.h"

class Display
{
    static std::vector<std::unique_ptr<Graph>> graphs;
    static std::unique_ptr<Display> display;

	int height;
	int width;
public:
    Display(int w, int h);
    ~Display();

    static Display * create(int w, int h);
    static void handleKeyPress(unsigned char, int, int);
    static void handleReshape(int, int);
    static void handleDraw();
    static void setup(int argc, char ** argv);

	void installGraph(std::unique_ptr<Graph> graph);
	void show(const char * title);
};
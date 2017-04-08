/**
 * 
 * Copyright 2015 : William Taylor : wi11berto@yahoo.co.uk
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * 	http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __ANN_DISPLAY__H_
#define __ANN_DISPLAY__H_

#include "Common.h"
#include "Graph.h"

// This class manages and sets up a window
class Display
{
private:
	// The height and width of the window itself
	int height;
	int width;
private:
	// Constructor & Deconstructor
	Display(int w, int h);
	~Display();

	// Handles key presses from the freeglut library
	static void handleKeyPress(unsigned char, int, int);
	// Handlesa window reshape event from the freeglut library
	static void handleReshape(int, int);
	// Handles the redraw event from the freeglut library
	static void handleDraw();
public:
	// Installs a graph to the display by storing the point then drawing it at the right time
	void installGraph(Graph * graph);
	// Sets up the freeglut library from command line arguments
	void setup(int argc, char * argv[]);
	// Shows the window with the following window title
	void show(const char * title);
private:
	// A vector a graphs that we will draw inside the window
	static std::vector<Graph *> graphs;
	// The displays instance 1 display per application
	static Display * graphDisplay;
public:
	// Get & Set functions for the displays instance
	static Display * create(int w, int h);
	static int release();
};

#endif
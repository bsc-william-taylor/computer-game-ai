
#include "Display.h"
#include "mlp.h"

// Some static declarations and function prototypes
std::vector<Graph *> Display::graphs = std::vector<Graph *>();
Display * Display::graphDisplay = 0;
void keyboard(int, int, int);

// Constructor & Deconstructor
Display::Display(int w, int h)
{
	height = h;
	width = w;
}

Display::~Display()
{
}

// Our release function which deletes the only instance
int Display::release()
{
	// if we have an instance allocated
	if (graphDisplay != 0) {
		// delete all the installed graphs
		for (auto& graph : graphs) {
			delete graph;
		}

		// then the display
		delete graphDisplay;
		// return 0 to indicate success
		return EXIT_SUCCESS;
	} else {
		// or 1 to indicate failure
		return EXIT_FAILURE;
	}
}

// Sets up the graphs display instance (1 per app)
Display * Display::create(int w, int h)
{
	// But first we make sure a seed is set for rand()
	srand((unsigned)time(NULL));
	// create the instance
	graphDisplay = new Display(w, h);
	// return the new instance
	return graphDisplay;
}

// Pushes a new graph into the vector to be drawn
void Display::installGraph(Graph * graph)
{
	graphs.push_back(graph);
}

void Display::setup(int argc, char ** argv)
{
	// Init the glut window library
	glutInit(&argc, argv);
	// then remove the console
	//FreeConsole();
}

void Display::show(const char * title) {
	// Here we set the parameters for the window
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(title);	// We create it here

	// Then setup our callbacks for the windowing system
	glutKeyboardFunc(Display::handleKeyPress);
	glutReshapeFunc(Display::handleReshape);
	glutDisplayFunc(Display::handleDraw);
	glutIdleFunc(Display::handleDraw);
	glutSpecialFunc(keyboard);

	// Optionally we output the gl version for debugging reasons
	std::cout << "GL Version " << glGetString(GL_VERSION) << std::endl;

	// We then enable smoothing of points and lines in opengl
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);

	// And enable blending to ensure these lines are drawn in the nicest way possible
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// We then say when the window closes just continue from glutMainLoop
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	glLineWidth(2.0f); // Set the line width to be slightly easier to see
	glPointSize(7.5); // Set the point size to be slightly easier to see
	glutMainLoop();	// The start the main window loop	
}

/**
 * The following are glut callback functions
 **/
double scale = 1;
double tx = 0;
double ty = 0;

// Here we handle the render event from glut
void Display::handleDraw() {
	// Clear the screen buffer and set the background colour to white
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// We then set the modelview matrix to be scaled and rotated
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// by an amount specified by the user
	glScaled(scale, scale, 1);
	glTranslated(tx, ty, 0.0);

	// We then draw some lines to show the axis's
	glBegin(GL_LINES);
		// We set there colour to orange
		glColor3d(1.0, 0.7, 0.0);
		// We then plot the points
		glVertex2f(-150000.0, 0);
		glVertex2f(150000.0, 0);
		glVertex2f(6.28318530718 / 2.0, 150000.0);
		glVertex2f(6.28318530718 / 2.0, -150000.0);
	glEnd();

	// After this we draw all installed graphs
	for (auto& graph : graphs) {
		graph->view();
	}

	// The swap the buffer to show the final image
	glutSwapBuffers();
}

// Here we handle key presses
void Display::handleKeyPress(unsigned char key, int, int) {
	// if the user presses escape we exit
	if (key == 27) {
		glutExit();
	}
	if (key == 't' || key == 'T')
		graphs[2]->getNetwork()->train(1000);
	// We scale the graph depending on the key press
	if (key == 'w' || key == 'W')
		scale += 0.05;
	if (key == 's' || key == 'S')
		scale -= 0.05;
	if (key == 'f' || key == 'F') // We also toggle fullscreen mode if they press f
		glutFullScreenToggle();
}

// Key we handle special keyboard presses
void keyboard(int key, int x, int y) {
	// depending on the arrow key we move the graph in that direction
	if (key == 102) {
		tx -= 0.05;
	} else if (key == 100) {
		tx += 0.05;
	} else if (key == 101) {
		ty -= 0.05;
	} else if (key == 103) {
		ty += 0.05;
	}
}

// When the window is resized this function is called by glut
void Display::handleReshape(int w, int h) {
	// We reset the project matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// The adjust the viewport based on the size
	glViewport(0, 0, w, h);
	glOrtho(0.0, 6.28318530718, -1.0, 1.0, -1.0, 1.0);
}

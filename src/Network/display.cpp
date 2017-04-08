
#include "display.h"
#include "mlp.h"

std::vector<std::unique_ptr<Graph>> Display::graphs;
std::unique_ptr<Display> Display::display;
double scale = 1, tx = 0, ty = 0;

void keyboard(int, int, int);

Display::Display(int w, int h) :
    height(h), width(w)
{
}

Display::~Display()
{
}

Display* Display::create(int w, int h)
{
    srand((unsigned)time(NULL));
    display = std::make_unique<Display>(w, h);
    return display.get();
}

void Display::installGraph(std::unique_ptr<Graph> graph)
{
    graphs.push_back(std::move(graph));
}

void Display::setup(int argc, char ** argv)
{
    glutInit(&argc, argv);
    FreeConsole();
}

void Display::show(const char * title)
{
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(title);
    glutKeyboardFunc(Display::handleKeyPress);
    glutReshapeFunc(Display::handleReshape);
    glutDisplayFunc(Display::handleDraw);
    glutIdleFunc(Display::handleDraw);
    glutSpecialFunc(keyboard);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glLineWidth(2.0f);
    glPointSize(7.5);
    glutMainLoop();
}

void Display::handleDraw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScaled(scale, scale, 1);
    glTranslated(tx, ty, 0.0);

    glBegin(GL_LINES);
    glColor3d(1.0, 0.7, 0.0);
    glVertex2f(-150000.0, 0);
    glVertex2f(150000.0, 0);
    glVertex2f(6.28318530718 / 2.0, 150000.0);
    glVertex2f(6.28318530718 / 2.0, -150000.0);
    glEnd();

    for (auto& graph : graphs)
    {
        graph->view();
    }

    glutSwapBuffers();
}

void Display::handleKeyPress(unsigned char key, int, int)
{
    if (key == 27)
        glutExit();
    if (key == 'w' || key == 'W')
        scale += 0.05;
    if (key == 's' || key == 'S')
        scale -= 0.05;
    if (key == 'f' || key == 'F')
        glutFullScreenToggle();
}

void keyboard(int key, int x, int y)
{
    if (key == GLUT_KEY_RIGHT)
        tx -= 0.05;
    if (key == GLUT_KEY_LEFT)
        tx += 0.05;
    if (key == GLUT_KEY_UP)
        ty -= 0.05;
    if (key == GLUT_KEY_DOWN)
        ty += 0.05;
}

void Display::handleReshape(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    glOrtho(0.0, 6.28318530718, -1.0, 1.0, -1.0, 1.0);
}

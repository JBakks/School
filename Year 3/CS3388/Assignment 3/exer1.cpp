// Josh Bakelaar
// 251139121
// Assignment 3

// Could not figure out part 2 of interaction

//Includes
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

// Point object
struct Point {
    float x;
    float y;
    int id;
};

// Child of point, NOde
struct Node : Point {
    bool hasHandle1, hasHandle2;
    Point handle1;
    Point handle2;
};

// Vectors to hold
vector<Node> nodes;
vector<Node> controlPoints;

int numPoints();
// Width and Height variables
int W, H;
int count = 0;

// Function which computes points for bezier curves to the 4th degree
float bezier4(float p0, float c1, float c2, float p2, float t){
    float point = pow((1-t),3) * p0 + 3 * pow((1-t),2)* t * c1 + 3 * (1-t) * pow(t,2) * c2 + pow(t,3) * p2;
    return point;
}

// Main display function

void display(){
    int count = 0;
    
    // Line segments to be drawn between points
    const int LINE_SEGMENTS = 200;

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    

    // Draw control point lines
    glLineWidth(3.0f);
    glColor3f(0.0, 1.0, 1.0);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xAAAA);
    glBegin(GL_LINES);
        for(Node i : nodes){
            if(count == 0 || count == nodes.size()-1){
                glVertex2f(i.handle1.x, i.handle1.y);
                glVertex2f(i.x, i.y);
            }else{
                glVertex2f(i.handle1.x, i.handle1.y);
                glVertex2f(i.handle2.x, i.handle2.y);

            }
            count++;
        }
    glEnd();
    count = 0;

    // Draw nodes as blue square points
    glColor3f(0.0, 0.0, 1.0);
    glPointSize(10.0f);
    glBegin(GL_POINTS);
        for(Node i : nodes){
            glVertex2f(i.x, i.y);
        }
    glEnd();

    glColor3f(0.0, 0.0, 0.0);

    // Draw smooth control points
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_POINTS);
        for(Node i : nodes){
            if(count == 0 || count == nodes.size()-1){
                glVertex2f(i.handle1.x, i.handle1.y);
            }else{
                glVertex2f(i.handle1.x, i.handle1.y);
                glVertex2f(i.handle2.x, i.handle2.y);
            }
            count++;
        }
    glEnd();
    count = 0;

    // Render each piece as an independent cubic Bezier curve
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);
        for(Node i : nodes){
            Node previous;
            if(count != 0){
                for(int j = 0; j < LINE_SEGMENTS; ++j){
                    float t = (float)j;
                    t /= LINE_SEGMENTS;
                    glVertex2f(bezier4(previous.x, previous.handle2.x, i.handle1.x, i.x, t), bezier4(previous.y, previous.handle2.y, i.handle1.y, i.y, t));

                }
            }
            // glVertex2f(i.x, i.y);
            count++;
            previous = i;
        }
    glEnd();
    count = 0;
    glutSwapBuffers();
}


// Creates a new point object
void newPoint(float x, float y){
    Node node = Node();
    node.x = x;
    node.y = y;
    if(nodes.empty() == true){
        node.handle1.x = x;
        node.handle1.y = y+0.5;
    }else{
        node.handle1.x = x;
        node.handle1.y = y+0.5;
        node.handle2.x = x;
        node.handle2.y = y-0.5;
    }
    nodes.push_back(node);
}

// Reset the board with e
void keyboardCallback(unsigned char key, int x, int y){
    // if key e is pressed
    if (key == 'e'){
        // iterate through nodes and pop all
        for(Node i : nodes){
            nodes.pop_back();
        }
        // refresh display
        glutPostRedisplay();
    }
}

// Finds the closest node to the mouse
int findNode(float x, float y) {
    // Iterate through all nodes
    for (int i = 0; i < nodes.size(); i++) {
        // Get the distance between cursor and node
        float dist = sqrt(pow(x - nodes[i].x, 2) + pow(y - nodes[i].y, 2));
        if (dist < 0.1) {
            // Return the position in nodes
            return i;
        }
    }
    // else return -1
    return -1;
}

// Mouse listener for clicks
void mouse(int button, int state, int x, int y) {
    float xf = ((float)x / (float)glutGet(GLUT_WINDOW_WIDTH)) * 2.0 - 1.0;
    float yf = -(((float)y / (float)glutGet(GLUT_WINDOW_HEIGHT)) * 2.0 - 1.0);
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int nodeIndex = findNode(xf, yf);
        if (nodeIndex == -1) {
            newPoint(xf, yf);
        }
        glutPostRedisplay();
    }
}

// Mouse listner for movement
void mouseMotion(int x, int y) {
    float xf = ((float)x / (float)glutGet(GLUT_WINDOW_WIDTH)) * 2.0 - 1.0;
    float yf = -(((float)y / (float)glutGet(GLUT_WINDOW_HEIGHT)) * 2.0 - 1.0);

    // Check if any node or control point is selected
    int selectedNode = findNode(xf, yf);
    if (selectedNode != -1) {
        nodes[selectedNode].x = xf;
        nodes[selectedNode].y = yf;
        nodes[selectedNode].handle1.x = xf;
        nodes[selectedNode].handle1.y = yf + 0.5;
        nodes[selectedNode].handle2.x = xf;
        nodes[selectedNode].handle2.y = yf - 0.5;
        glutPostRedisplay();
    }
}

//Main function
int main(int argc, char** argv) {

    // Get command line arguments for Width and Height
    istringstream(argv[1]) >> W;
    istringstream(argv[2]) >> H;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(W, H);
    glOrtho(0, W, 0, H, -1, 1);
    glViewport(0, 0, W, H);    

    glutCreateWindow("Assignment 3 | exer1");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutKeyboardFunc(keyboardCallback);

    glutMainLoop();

    return 0;
}

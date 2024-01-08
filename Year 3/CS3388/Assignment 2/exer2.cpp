#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <functional>
#include <algorithm>
#include <sstream>
using namespace std;

static inline double frand () {
    double x = (( double ) rand () ) / ( double ) RAND_MAX ;
    if ( rand () % 2) {
        x *= -1.0;
    }
    return x;
}

int pickCorner() {
    int table[] = {-1, 1};
    int index = rand() % 2;
    int random = table[index];
    return random;
}

int main(int argc, char** argv)
{   
    int iterate;
    int screenW;
    int screenH;
    GLFWwindow* window;
    double previousPoint[2]; 
    double previousCorner[2];

    std::istringstream (argv[1]) >> iterate;
    std::istringstream (argv[2]) >> screenW;
    std::istringstream (argv[3]) >> screenH;


    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(screenW, screenH, "Assignment 2 | Exercise 2", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    glMatrixMode ( GL_PROJECTION );
    glLoadIdentity ();
    glOrtho(-1.1 , 1.1, -1.1, 1.1, -1, 1);
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    double point1[2] = {frand(), frand()};
    previousPoint[0] = point1[0];
    previousPoint[1] = point1[1];

    int corner1[2] = {pickCorner(), pickCorner()};
    previousCorner[0] = corner1[0];
    previousCorner[1] = corner1[1];

    for (int i = 0; i < iterate; i++) {
        // second corner, not diagonally opposite the first one
        int corner2[2] = {pickCorner(), pickCorner()};
        while (corner2[0] == previousCorner[0] * -1 && corner2[1] == previousCorner[1] * -1) {
            corner2[0] = pickCorner();
            corner2[1] = pickCorner();
        } 

        previousCorner[0] = corner2[0];
        previousCorner[1] = corner2[1];

        // second point, halfway between the first point and and the second corner
        double point2[2] = {(previousCorner[0] + previousPoint[0])/2, (previousCorner[1] + previousPoint[1])/2};

        // place a dot at point2
        glPointSize(2.0);
        glColor3f(0, 0, 0);
        //glTranslatef(5,5,0);

        glBegin(GL_POINTS);
            glVertex2f(point2[0], point2[1]);
        glEnd();
        //glTranslatef(-5,-5,0);
        previousPoint[0] = point2[0];
        previousPoint[1] = point2[1];
    }
    glfwSwapBuffers ( window );

    while (! glfwWindowShouldClose( window ))
    {
        glfwPollEvents();
        // glfwSwapBuffers ( window );
    }
    glfwTerminate();
    return 0;
}
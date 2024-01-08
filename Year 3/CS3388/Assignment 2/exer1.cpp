#include <GLFW/glfw3.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

float angle = 0.0;

struct Vertex {
    float x;
    float y;
};

std::vector<Vertex> readFile() {
    std::vector<Vertex> vertices;
    std::ifstream file("dog.txt");
    float x, y;
    while (file >> x >> y) {
        Vertex vertex = {x, y};
        vertices.push_back(vertex);
    }
    file.close();
    return vertices;
}

std::vector<Vertex> vertices = readFile();


int main(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 640, "Assignment 2 | Exercise 1", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glMatrixMode ( GL_PROJECTION );
    glLoadIdentity ();
    glOrtho(0 , 60, 0, 60, -1, 1);

    while (! glfwWindowShouldClose( window ))
    {
        angle += 1;

        if(angle >= 360) angle =0.0;        

        /* Poll for and process events (mouse , keyboard , etc .) */
        glfwPollEvents ();

        // Specifies the viewing volume to be (𝑙𝑒𝑓 𝑡, 𝑟𝑖𝑔ℎ𝑡, 𝑏𝑜𝑡𝑡𝑜𝑚, 𝑡𝑜𝑝) = (0, 60, 0, 60)

        /* Color the whole view as glClearColor . By default , black . */
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0,1.0,1.0,1.0);

            
        for(int i = 0; i<8; i++){
            float x = 30 + 25 * cos((i*45) * M_PI/4);
            float y = 30 + 25 * sin((i*45) * M_PI /4);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity(); 

            glTranslatef(x, y, 0.0);
            glRotatef(angle, 0.0f, 0.0f, 1.0f);

            glColor3f(0, 0, 0);
            glBegin(GL_LINE_STRIP);
                for (const Vertex& vertex : vertices) {
                    glVertex2f(vertex.x, vertex.y);
                }
            glEnd();
        }

        glfwSwapBuffers ( window );
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

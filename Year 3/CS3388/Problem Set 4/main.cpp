#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280,1000, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    std::vector<float> star = {0, 10, 2.5, 2.5, 10, 2.5, 4, -2.5, 7, -10, 0, -5, -7, -10, -4, -2.5, -10, 2.5, -2.5, 2.5, 0, 10};

    float v1x = 10* 0.5, v1y = 10*1.5388, v2x = 10*1.30902,
    v2y = 10*0.951056, v3x = 10*1.618034, v3y = 0;
    std::vector<float> decagon = {5, 15.388, 13.0902, 9.51056, 16.1803, 0, 13.0902, -9.51056, 5, -15.388, -5, -15.388,
-13.0902, -9.51056, -16.1803, 0, -13.0902, 9.51056, -5, 15.388, 5, 15.388};


    glMatrixMode ( GL_PROJECTION );
    glLoadIdentity ();
    glOrtho (-20, 20, -20, 20, -1, 1);

    float deltaT = 0.005, t = 0, vx , vy;

    /* Loop until the user closes the window */
    while (! glfwWindowShouldClose ( window ) )
    {
    //...
    glBegin ( GL_LINE_STRIP );
    for ( int i = 0; i < star . size (); i +=2) {
    vx = lerp( star [ i ] , decagon[ i ] , t );
    vy = lerp ( star [ i +1], decagon[ i +1] , t );
    glVertex2f ( vx , vy );
    }
    glEnd ();

    if ( t > 1.0f || t < 0.0f ) {
    deltaT *= -1.0f;
    }
    t += deltaT ;
    //...
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Poll for and process events */
        glfwPollEvents();
        
		/* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

		//Draw a pink triangle with vertices (0, 0.5), (0.5,−0.25), (−0.5,−0.25).
        glBegin(GL_TRIANGLES);
        glColor3f(0.8427, 0.5733, 0.91);
        glVertex2f(0,0.5);
        glVertex2f(0.5,-0.25);
        glVertex2f(-0.5,-0.25);
        glEnd();
        
		/* Swap front and back buffers */
        glfwSwapBuffers(window);

    }

    glfwTerminate();
    return 0;
}

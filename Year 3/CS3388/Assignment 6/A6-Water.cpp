// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include "Axes.hpp"
#include "cameraGlobe.hpp"

#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <iostream>
#include <vector>

#include "PlaneMesh.hpp"

// static float angle1 = glm::radians(-45.0f);
// static float angle2 = glm::radians(-45.0f);

// double x, y;
// static double prevX, prevY;
// int clicked = 0;

// void cameraGlobe(glm::mat4& V, float startPos) {
//     static float rot = 17.4f;
//     double currTime = glfwGetTime();
//     static double prevTime = glfwGetTime();
//     float dtime = (currTime - prevTime), varx = 0.0f, vary = 0.0f, varz = 0.0f, velocity = 6.0f;
//     prevTime = currTime;

//     switch (glfwGetKey(window, GLFW_KEY_UP)) {
//     case GLFW_PRESS:
//         rot = glm::max(rot - dtime * velocity, 0.1f);
//         break;
// 	}

// 	switch (glfwGetKey(window, GLFW_KEY_DOWN)) {
// 		case GLFW_PRESS:
// 			rot = glm::min(rot + dtime * velocity, 50.0f);
// 			break;
// 	}

// 	switch (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)) {
// 		case GLFW_PRESS:
// 			glfwGetCursorPos(window, &x, &y);
// 			if (clicked == 1) {
// 				varx = glm::radians((x - prevX) * 0.1f);
// 				angle1 += varx;
// 				if (angle1 < 0.0f) {
// 					angle1 += glm::radians(360.0f);
// 				}
// 				if (angle1 > glm::radians(360.0f)) {
// 					angle1 -= glm::radians(360.0f);
// 				}
// 				vary = glm::radians((y - prevY) * 0.1f);
// 				angle2 += vary;
// 				if (angle2 < glm::radians(-89.0f)) {
// 					angle2 = glm::radians(-89.0f);
// 				}
// 				if (angle2 > glm::radians(89.0f)) {
// 					angle2 = glm::radians(89.0f);
// 				}
// 			} else {
// 				prevX = x;
// 				prevY = y;
// 				clicked = 1;
// 			}

// 			prevX = x;
// 			prevY = y;
// 			break;
// 		case GLFW_RELEASE:
// 			clicked = 0;
// 			break;
// 	}

//     glm::vec3 Pos(rot * glm::sin(angle2) * glm::cos(angle1),
//                        rot * glm::cos(angle2),
//                        rot * glm::sin(angle2) * glm::sin(angle1));

//     V = glm::lookAt(Pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
// }

//////////////////////////////////////////////////////////////////////////////
// Main
//////////////////////////////////////////////////////////////////////////////

int main( int argc, char* argv[])
{

	///////////////////////////////////////////////////////
	float screenW = 750;
	float screenH = 750;
	float stepsize = 1.0f;

	float xmin = -10;
	float xmax = 10;

	if (argc > 1 ) {
		screenW = atoi(argv[1]);
	}
	if (argc > 2) {
		screenH = atoi(argv[2]);
	}
	if (argc > 3) {
		stepsize = atof(argv[3]);
	}
	if (argc > 4) {
		xmin = atof(argv[4]);
	}
	if (argc > 5) {
		xmax = atof(argv[5]);
	}


	///////////////////////////////////////////////////////

	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( screenW, screenH, "Josh's Waves", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	Axes axes(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(4.0f, 4.0f, 4.0f));

	PlaneMesh plane(xmin, xmax, stepsize);
	
	// PlaneMesh boat("Assets/boat.ply", "Assets/boat.bmp", 1);
	// PlaneMesh head("Assets/head.ply", "Assets/head.bmp", 1);
	// PlaneMesh eyes("Assets/eyes.ply", "Assets/eyes.bmp", 1);


	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.2f, 0.2f, 0.3f, 0.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glDisable(GL_CULL_FACE);

	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), screenW/screenH, 0.001f, 1000.0f);

	glm::vec3 lightpos(5.0f, 30.0f, 5.0f);
	glm::vec4 color1(1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	// Projection = glm::mat4(1.0f);
	glLoadMatrixf(glm::value_ptr(Projection));

	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
    glm::vec3 eye = {5.0f, 5.0f, 5.0f};
    glm::vec3 up = {0.0f, 1.0f, 0.0f};
    glm::vec3 center = {0.0f, 0.0f, 0.0f};
    //glm::mat4 V;

    glm::mat4 V = glm::mat4(1.0f);

    do{
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 M = glm::mat4(1.0f);
        glm::mat4 MV = V * M;
        glm::mat4 MVP = Projection * MV;
        glLoadMatrixf(glm::value_ptr(V));

        // Control the camera in the window
        cameraGlobe(V,20,window);

		// cameraThirdPerson(M, V, window)

		//draw axes
		//axes.draw();
		// draw plane
		plane.draw(lightpos, V, Projection);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	return 0;
}


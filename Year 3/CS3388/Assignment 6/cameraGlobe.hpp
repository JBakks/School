#ifndef CAMERA_GLOBE_HPP
#define CAMERA_GLOBE_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

// This is the GLFW window variable that will be used in cameraGlobe function
double x, y;
static double prevX, prevY;
int clicked = 0;

static float angle1 = glm::radians(-45.0f);
static float angle2 = glm::radians(-45.0f);

// CameraGlobe function definition
void cameraGlobe(glm::mat4& V, float startPos, GLFWwindow* window) {
    static float rot = 150.0f;
    double currTime = glfwGetTime();
    static double prevTime = glfwGetTime();
    float dtime = (currTime - prevTime), varx = 0.0f, vary = 0.0f, varz = 0.0f, velocity = 6.0f;
    prevTime = currTime;

    switch (glfwGetKey(window, GLFW_KEY_UP)) {
    case GLFW_PRESS:
        rot = glm::max(rot - dtime * velocity, 0.1f);
        break;
	}

	switch (glfwGetKey(window, GLFW_KEY_DOWN)) {
		case GLFW_PRESS:
			rot = glm::min(rot + dtime * velocity, 50.0f);
			break;
	}

	switch (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)) {
		case GLFW_PRESS:
			glfwGetCursorPos(window, &x, &y);
			if (clicked == 1) {
				varx = glm::radians((x - prevX) * 0.1f);
				angle1 += varx;
				if (angle1 < 0.0f) {
					angle1 += glm::radians(360.0f);
				}
				if (angle1 > glm::radians(360.0f)) {
					angle1 -= glm::radians(360.0f);
				}
				vary = glm::radians((y - prevY) * 0.1f);
				angle2 += vary;
				if (angle2 < glm::radians(-89.0f)) {
					angle2 = glm::radians(-89.0f);
				}
				if (angle2 > glm::radians(89.0f)) {
					angle2 = glm::radians(89.0f);
				}
			} else {
				prevX = x;
				prevY = y;
				clicked = 1;
			}

			prevX = x;
			prevY = y;
			break;
		case GLFW_RELEASE:
			clicked = 0;
			break;
	}

    glm::vec3 Pos(rot * glm::sin(angle2) * glm::cos(angle1),
                       rot * glm::cos(angle2),
                       rot * glm::sin(angle2) * glm::sin(angle1));

    V = glm::lookAt(Pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

#endif // CAMERA_GLOBE_HPP

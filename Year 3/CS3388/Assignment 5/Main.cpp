/* 
* Josh Bakelaar
* CS3388
* Assignment 5
* April 10, 2023
*/

// Include necessary libraries
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <functional>
#include <vector>
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include "math.h"
#include "TriTable.hpp"

// Create OpenGL window
GLFWwindow *window;

// Window width and height
const float WIDTH = 800;
const float HEIGHT = 600;
const float stepsize = 0.05f;
glm::mat4 V;

// Help to generate points returns float
float f1(float x, float y, float z)
{
	return y - sin(x) * cos(z);
}

// Help to generate points returns points
float f2(float x, float y, float z)
{
	return (x * x) - (y * y) - (z * z) - z;
}

// Function for loading shaders from one of the lessons in class
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){
    // Create IDs
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Get the shader code and put it into a string
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open()){
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }else{
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
        getchar();
        return 0;
    }

	// Get the shader code and put it inot a string
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

	// Print status
    printf("Compiling shader : %s\n", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }

	// Print Status
    printf("Compiling shader : %s\n", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }

	// Print linking!
    printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

	// Detach and take down shaders
    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

	// Return progrma id
    return ProgramID;
}

// Function used for writing to ply files
void writePLY(const std::vector<GLfloat> *vertices, const std::vector<GLfloat> *normals, std::string fileName) {
    // Print status
	std::cout << "Generating PLY data." << std::endl;
    std::ofstream outputFile(fileName);
	// Print header for ply file
    outputFile << "ply\n";
    outputFile << "format ascii 1.0\n";
    outputFile << "element vertex " << vertices->size() / 3 << "\n";
    outputFile << "property float x\n";
    outputFile << "property float y\n";
    outputFile << "property float z\n";
    outputFile << "property float nx\n";
    outputFile << "property float ny\n";
    outputFile << "property float nz\n";
    outputFile << "element face " << vertices->size() / 3 << "\n";
    outputFile << "property list uchar uint vertex_indices\n";
    outputFile << "end_header\n";

	// get vertices and normals
    const GLfloat* vPtr = vertices->data();
    const GLfloat* nPtr = normals->data();
    auto it = vertices->begin();
	auto it_n = normals->begin();

	// Put vertices in
	while (it != vertices->end()) {
		outputFile << *it << " " << *(it+1) << " " << *(it+2)
			<< " " << *it_n << " " << *(it_n+1) << " " << *(it_n+2) << "\n";
		it += 3;
		it_n += 3;
	}

	// Put indices in
	std::size_t i = 0, j = 0;
	while (i < vertices->size()) {
		outputFile << "3 " << j << " " << j + 1 << " " << j + 2 << "\n";
		i += 3;
		j += 3;
	}

	// close
    outputFile.close();
}

// varibles for globe camera
static float angle = glm::radians(-45.0f);
static float theta = glm::radians(-45.0f);
static double lastX, lastY;
double x, y;
bool clicked = true;


/**
 * SECTION FOR DRAWING A BOX
*/
void box(float min, float max){
	glLineWidth(2.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex3f(min, min, min);
		glVertex3f(max, min, min);
	glEnd();
		glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex3f(min, min, min);
		glVertex3f(min, max, min);
	glEnd();
		glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex3f(min, min, min);
		glVertex3f(min, min, max);
	glEnd();
	glColor3f(1.0f, 1.0f, 1.0f);
 	glBegin(GL_LINES);
        glVertex3f(min, max, min);
        glVertex3f(max, max, min);
	glEnd();

 	glBegin(GL_LINES);
        glVertex3f(max, max, min);
        glVertex3f(max, min, min);
	glEnd();

	glBegin(GL_LINES);
        glVertex3f(min, max, min);
        glVertex3f(min, max, max);
    glEnd();

	glBegin(GL_LINES);
        glVertex3f(min, max, max);
        glVertex3f(max, max, max);
	glEnd();

 	glBegin(GL_LINES);
        glVertex3f(max, max, max);
        glVertex3f(max, max, min);
	glEnd();

	glBegin(GL_LINES);
        glVertex3f(max, max, max);
        glVertex3f(max, min, max);
	glEnd();

 	glBegin(GL_LINES);
        glVertex3f(max, min, max);
        glVertex3f(max, min, min);
	glEnd();

	glBegin(GL_LINES);
        glVertex3f(max, min, max);
        glVertex3f(min, min, max);
	glEnd();

	glBegin(GL_LINES);
        glVertex3f(min, min, max);
        glVertex3f(min, max, max);
	glEnd();
}

/**
 * CAMERA CONTROLS
*/
void cameraGlobe(glm::mat4& V, float start) {
    static float r = 17.4f;
    double currentTime = glfwGetTime();
    static double lastTime = glfwGetTime();
    float deltaTime = (currentTime - lastTime);
    lastTime = currentTime;
    float dx = 0.0f, dy = 0.0f, dz = 0.0f;
    float speed = 6.0f;

	// if up zoom out
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        r = glm::max(r - deltaTime * speed, 0.1f);
    }
	// if down zoom in
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        r = glm::min(r + deltaTime * speed, 50.0f);
    }
	// If click move around
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        glfwGetCursorPos(window, &x, &y);
		// if not clicked get the x and set to last
        if(!clicked){
            lastX = x;
            lastY = y;
            clicked = true;
        }
		// if lastx and last y isnt in the center (first run)
        if (lastX != 0.0 && lastY != 0.0) {
			// calculate spherical camera coorediantes
            dx = glm::radians((x - lastX) * 0.1f);
            angle += dx;
            if (angle < 0.0f) {
                angle += glm::radians(360.0f);
            }
            if (angle > glm::radians(360.0f)) {
                angle -= glm::radians(360.0f);
            }
            dy = glm::radians((y - lastY) * 0.1f);
            theta += dy;
            if (theta < glm::radians(-89.0f)) {
                theta = glm::radians(-89.0f);
            }
            if (theta > glm::radians(89.0f)) {
                theta = glm::radians(89.0f);
            }
        }
		// update last x and y
        lastX = x;
        lastY = y;
    }
	// If released click = flase
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE){
        clicked = false;
    }

	// Update position with spherical camera coords
    glm::vec3 position(r * glm::sin(theta) * glm::cos(angle),
                       r * glm::cos(theta),
                       r * glm::sin(theta) * glm::sin(angle));

    V = glm::lookAt(position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

/**
 * MARCHING CUBES ALGORITHM
*/
std::vector<float> marching_cubes(std::function<float(float, float, float)> f, float isovalue, float min, float max, float stepsize) {
    std::vector<float> vertices;
    std::array<float, 10> value;
    int which;
    int* cubeVetices;
    std::vector<float> xs((max - min) / stepsize);
	// generate three vectors which represent sampling pojnts in scalr field and fill them
    std::generate(xs.begin(), xs.end(), [min, stepsize, i = 0]() mutable
	{
		// incrementing stepsize
        float x = min + i * stepsize;
        i++;
        return x;
    });
	// same as one before for y
    std::vector<float> ys((max - min) / stepsize);
    std::generate(ys.begin(), ys.end(), [min, stepsize, i = 0]() mutable
	{
        float y = min + i * stepsize;
        i++;
        return y;
    });

	// same as previous for z
    std::vector<float> zs((max - min) / stepsize);
    std::generate(zs.begin(), zs.end(), [min, stepsize, i = 0]() mutable
	{
        float z = min + i * stepsize;
        i++;
        return z;
    });

	// iterate over each sampling point evaluating the scalr field at each to detreming if interection
    auto x = xs.begin();
	while (x != xs.end())
	{
		auto y = ys.begin();
		while (y != ys.end())
		{
			auto z = zs.begin();
			while (z != zs.end())
			{
				value[0] = f(*x, *y, *z);
				value[1] = f(*x + stepsize, *y, *z);
				value[2] = f(*x + stepsize, *y, *z + stepsize);
				value[3] = f(*x, *y, *z + stepsize);
				value[4] = f(*x, *y + stepsize, *z);
				value[5] = f(*x + stepsize, *y + stepsize, *z);
				value[6] = f(*x + stepsize, *y + stepsize, *z + stepsize);
				value[7] = f(*x, *y + stepsize, *z + stepsize);

				which = 0;
				if (value[0] < isovalue) which |= 1;
				if (value[1] < isovalue) which |= 2;
				if (value[2] < isovalue) which |= 4;
				if (value[3] < isovalue) which |= 8;
				if (value[4] < isovalue) which |= 16;
				if (value[5] < isovalue) which |= 32;
				if (value[6] < isovalue) which |= 64;
				if (value[7] < isovalue) which |= 128;

				cubeVetices = marching_cubes_lut[which];
				int i = 0;
				while (cubeVetices[i] != -1)
				{
					int j = 0;
					while (j < 3) {
						float vertx = *x + stepsize * vertTable[cubeVetices[i + j]][0];
						float verty = *y + stepsize * vertTable[cubeVetices[i + j]][1];
						float vertz = *z + stepsize * vertTable[cubeVetices[i + j]][2];
						vertices.push_back(vertx);
						vertices.push_back(verty);
						vertices.push_back(vertz);
						j++;
					}
					i += 3;
				}
				z += 1;
			}
			y += 1;
		}
		x += 1;
	}
	return vertices;
}

/**
 * Function for computing normals
*/
std::vector<float> compute_normals(const std::vector<float>& vertices) {
    std::vector<float> vert_normals;
    vert_normals.reserve(vertices.size());

    for (size_t i = 0; i < vertices.size(); i += 9) {
        
        glm::vec3 v1(vertices[i], vertices[i + 1], vertices[i + 2]);
        glm::vec3 v2(vertices[i + 3], vertices[i + 4], vertices[i + 5]);
        glm::vec3 v3(vertices[i + 6], vertices[i + 7], vertices[i + 8]);

        glm::vec3 edge1 = v2 - v1;
        glm::vec3 edge2 = v3 - v2;
        glm::vec3 tri_norm = glm::normalize(glm::cross(edge1, edge2));

        for (int j = 0; j < 3; j++) {
            vert_normals.emplace_back(tri_norm.x);
            vert_normals.emplace_back(tri_norm.y);
            vert_normals.emplace_back(tri_norm.z);
        }
    }
    return vert_normals;
}

int main(){
	float isovalue = 0;
	float min = -5;
	float max = 5;
	if (!glfwInit()){
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	window = glfwCreateWindow(WIDTH, HEIGHT, "Josh's Cubes", NULL, NULL);
	if (window == NULL){
		fprintf(stderr, "Failed to open GLFW window.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK){
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	std::vector<float> marchingvertices = marching_cubes
	(
		f1,
		isovalue,
		min,
		max,
		stepsize
	);

	std::vector<float> marchingNormals = compute_normals
	(
			marchingvertices
	);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.2f, 0.2f, 0.4f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	int marchingNormalsSize = marchingNormals.size();

	writePLY(&marchingvertices, &marchingNormals, "points.ply");
	GLuint shaderProgram = LoadShaders("PhongTexture.vertexshader", "PhongTexture.fragmentshader");
	GLuint VAO;
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	GLuint marchingVBO;
	glCreateBuffers(1, &marchingVBO);
	glBindBuffer(GL_ARRAY_BUFFER, marchingVBO);
	glNamedBufferData(marchingVBO, marchingvertices.size() * sizeof(float), marchingvertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	GLuint normalVBO;
	glCreateBuffers(1, &normalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glNamedBufferData(normalVBO, marchingNormals.size() * sizeof(float), marchingNormals.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	GLuint MVPID = glGetUniformLocation(shaderProgram, "MVP");
	GLuint VID = glGetUniformLocation(shaderProgram, "V");
	GLuint MID = glGetUniformLocation(shaderProgram, "M");
	GLuint LightPosID = glGetUniformLocation(shaderProgram, "LightPosition_worldspace");
	GLuint colorID = glGetUniformLocation(shaderProgram, "modelcolor");
	GLuint alphaID = glGetUniformLocation(shaderProgram, "alpha");
	glm::mat4 V(1.0f);
	glm::vec3 lightPos(5.0f, 5.0f, 5.0f);
	glm::vec4 color(0.1f, 0.5f, 0.3f, 1.0f);
	
	do{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.001f, 1000.0f);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadMatrixf(glm::value_ptr(Projection));
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glm::mat4 M = glm::mat4(1.0f);
		glm::mat4 MV = V * M;
		glm::mat4 MVP = Projection * MV;
		glLoadMatrixf(glm::value_ptr(V));
		cameraGlobe(V, 5);
		box(min, max);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glUniformMatrix4fv(MVPID, 1, GL_FALSE, glm::value_ptr(MVP));
		glUniformMatrix4fv(VID, 1, GL_FALSE, glm::value_ptr(V));
		glUniformMatrix4fv(MID, 1, GL_FALSE, glm::value_ptr(M));
		glUniform3fv(LightPosID, 1, glm::value_ptr(lightPos));
		glUniform4fv(colorID, 1, glm::value_ptr(color));
		glUniform1f(alphaID, 64.0f);
		int marchingSize = marchingvertices.size()/3;
		glDrawArrays(GL_TRIANGLES, 0, marchingSize);
		glBindVertexArray(0);
		glUseProgram(0);
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
    	glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		    glfwWindowShouldClose(window) == 0);

	glfwTerminate();
	return 0;
}

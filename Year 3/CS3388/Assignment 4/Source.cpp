// Josh Bakelaar (251139121)
// Assignment 4
// Recreate Links House from Legend of Zelda: Ocarina of Time 3DS

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "loadBitmap.cpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Controls size of window
float WIDTH = 1200;
float HEIGHT = 800;

// Controls camera
glm::vec3 cameraPos = glm::vec3(0.5f, 0.4f, 0.5f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 direction;

// Object for holding face data
struct TriData {
	glm::ivec3 indices;
};

// Object for vertex data
struct VertexData {
    // Position
    glm::vec3 position;
    // Normal
    glm::vec3 normal;
    // Color
    glm::vec3 color;
    // Texture Coords
    glm::vec2 texCoord;
};

// camControl
// takes in window where you are controlling the camera
void camControl(GLFWwindow* window) {
	// variables for controlling the speed
	const float cameraSpeed = 0.03f;
	const float rotateSpeed = 0.02f;

	// if up is pressed move forward
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		cameraPos += cameraSpeed * cameraFront;
	}
	// if down is pressed move backwards
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		cameraPos -= cameraSpeed * cameraFront;
	}
	// if left is pressed turn left
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), rotateSpeed, cameraUp);
		cameraFront = glm::vec3(rotation * glm::vec4(cameraFront, 1.0f));
	}
	// if right is pressed turn right
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), -rotateSpeed, cameraUp);
		cameraFront = glm::vec3(rotation * glm::vec4(cameraFront, 1.0f));
	}
}

// readPLYFile
// function used to read the ply files provided
// takes in the plyfile name, vertices vector, and faces vector.
void readPLYFile(const std::string& fileName, std::vector<VertexData>& vertices, std::vector<TriData>& faces) {
	// Read file
    std::ifstream file(fileName);

	// If file did not get read throw an error and exit out of function
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return;
    }

    int numVertices = 0;
    int numFaces = 0;

	// Not all files contain these so make booleans to check
    bool norms = false;
    bool colors = false;
    bool texCoords = false;

    std::string line;
    std::stringstream ss;
	// Read PLY header
    while (getline(file, line)) {
		ss.clear();
		// If line contains the following...
        if (line.find("element vertex") != std::string::npos) {
			// get the line
            ss << line;
			// ignore the first 14 chars
            ss.ignore(14);
			// get the number of vertices
            ss >> numVertices;
		// If line contains the following...
        } else if (line.find("element face") != std::string::npos) {
            ss << line;
            ss.ignore(12);
			// get number of faces
            ss >> numFaces;
		// If line contains the following...
        } else if (line.find("property float nx") != std::string::npos) {
			// There are norms
            norms = true;
        } else if (line.find("property uchar red") != std::string::npos) {
			// There are colors
            colors = true;
        } else if (line.find("property float u") != std::string::npos) {
			// There are texure coordinates
            texCoords = true;
		// If line contains the following...
        } else if (line.find("end_header") != std::string::npos) {
			// end of header
            break;
        }
    }

    // Read vertex data
	for (int i = 0; i < numVertices; i++) {
		// Create new vertex
		VertexData vertex;
		// get the line
		getline(file, line);
		// clear string stream and put in the line
		ss.clear();
		ss << line;

		// All ply files have x y z so put them in the vertex data
		ss >> vertex.position.x >> vertex.position.y >> vertex.position.z;

		// If the line has norms put them in the vertex data
		if (norms) {
			ss >> vertex.normal.x >> vertex.normal.y >> vertex.normal.z;
		}
		// If the line has colors put them in the vertex data
		if (colors) {
			ss >> vertex.color.r >> vertex.color.g >> vertex.color.b;
			// make them rgb code
			vertex.color /= 255.0f;
		}

		// If the line has texture coordinates put them in the vertex data
		if (texCoords) {
			ss >> vertex.texCoord.x >> vertex.texCoord.y;
		}
		// Add the vertex to vertices vector
		vertices.push_back(vertex);
	}

    // Read face data
    for (int i = 0; i < numFaces; i++) {
		// Create face object
        TriData face;
		// Get the line
        getline(file, line);
		// Clear the String stream and add it in
        ss.clear();
        ss << line;

		// Get the number of indices from the first character in the line
        int numIndices;
        ss >> numIndices;

		// number of indices
        if (numIndices == 3) {
			// create the indice vec3
            glm::vec3 indices;
			// Put the xyz in the indice
            ss >> indices.x >> indices.y >> indices.z;
			// Set the face indices = to this indcies
            face.indices = indices;
			// add the face to faces
            faces.push_back(face);
        }
    }
}

class TexturedMesh {
	std::vector<VertexData> vertices;
	std::vector<TriData> faces;
	// Vertex Position, Texture Coord Position, Indice Position, TextureId, VAOID, Shader
	GLuint posVBO, texVBO, indVBO, texID, vaoID, programID; 

public:
	TexturedMesh(const std::string& plyFilePath, const std::string& bmpFilePath)
	{
		// read vertices and faces from PLY file
		readPLYFile(plyFilePath, vertices, faces);

		// Create the shaders
		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		std::string VertexShaderCode = "\
			#version 330 core\n\
				// Input vertex data, different for all executions of this shader.\n\
				layout(location = 0) in vec3 vertexPosition;\n\
				layout(location = 1) in vec2 uv;\n\
				// Output data ; will be interpolated for each fragment.\n\
				out vec2 uv_out;\n\
				// Values that stay constant for the whole mesh.\n\
				uniform mat4 MVP;\n\
				void main(){ \n\
					// Output position of the vertex, in clip space : MVP * position\n\
					gl_Position =  MVP * vec4(vertexPosition,1);\n\
					// The color will be interpolated to produce the color of each fragment\n\
					uv_out = uv;\n\
		}\n";

		// Read the Fragment Shader code from the file
		std::string FragmentShaderCode = "\
            #version 330 core\n\
            in vec2 uv_out; \n\
            uniform sampler2D tex;\n\
            void main() {\n\
                gl_FragColor = texture(tex, uv_out);\n\
            }\n";
		char const* VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
		glCompileShader(VertexShaderID);

		// Compile Fragment Shader
		char const* FragmentSourcePointer = FragmentShaderCode.c_str();
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
		glCompileShader(FragmentShaderID);

		programID = glCreateProgram();
		glAttachShader(programID, VertexShaderID);
		glAttachShader(programID, FragmentShaderID);

		glLinkProgram(programID);

		glDetachShader(programID, VertexShaderID);
		glDetachShader(programID, FragmentShaderID);

		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);

		// load bitmap image
		GLuint width, height;
		unsigned char* image;
		loadARGB_BMP(bmpFilePath.c_str(), &image, &width, &height);

		// create texture object
		glGenTextures(1, &texID);
		glBindTexture(GL_TEXTURE_2D, texID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		glGenVertexArrays(1, &vaoID);
		glGenBuffers(1, &posVBO);
		glGenBuffers(1, &texVBO);
		glGenBuffers(1, &indVBO);

		glBindVertexArray(vaoID);

		// create vertex buffer object for face indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indVBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(TriData), faces.data(), GL_STATIC_DRAW);

		// create vertex buffer object for vertex positions
		glBindBuffer(GL_ARRAY_BUFFER, posVBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexData), vertices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)0);

		// create vertex buffer object for texture coordinates
		glBindBuffer(GL_ARRAY_BUFFER, texVBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexData), vertices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(offsetof(VertexData, texCoord.x)));

		// create vertex array object
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void draw(const glm::mat4& MVP) const
	{
		GLuint MatrixID = glGetUniformLocation(programID, "MVP");

		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texID);

		glUseProgram(programID);
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, value_ptr(MVP));

		glBindVertexArray(vaoID);
		glDrawElements(GL_TRIANGLES, faces.size() * 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glUseProgram(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
	}
};

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Assignment 4", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glewInit();

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	TexturedMesh bottles("LinksHouse/Bottles.ply", "LinksHouse/bottles.bmp");
	TexturedMesh curtains("LinksHouse/Curtains.ply", "LinksHouse/curtains.bmp");
	TexturedMesh doorBG("LinksHouse/DoorBG.ply", "LinksHouse/doorbg.bmp");
	TexturedMesh floor("LinksHouse/Floor.ply", "LinksHouse/floor.bmp");
	TexturedMesh metalObjects("LinksHouse/MetalObjects.ply", "LinksHouse/metalobjects.bmp");
	TexturedMesh patio("LinksHouse/Patio.ply", "LinksHouse/patio.bmp");
	TexturedMesh table("LinksHouse/Table.ply", "LinksHouse/table.bmp");
	TexturedMesh walls("LinksHouse/Walls.ply", "LinksHouse/walls.bmp");
	TexturedMesh windowBG("LinksHouse/WindowBG.ply", "LinksHouse/windowbg.bmp");
	TexturedMesh wood("LinksHouse/WoodObjects.ply", "LinksHouse/woodobjects.bmp");

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), WIDTH / HEIGHT, 0.001f, 1000.0f);

	glClearColor(0.2f, 0.2f, 0.3f, 0.0f);

	do {
		glLoadMatrixf(glm::value_ptr(projection));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		// MVP for camera position so camera appears to move
		glm::mat4 V = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		glm::mat4 M = glm::mat4(1.0f);
		glm::mat4 MV = V * M;
		glm::mat4 MVP = projection * V * M;
		glLoadMatrixf(glm::value_ptr(V));

		// Control the camera in the window
		camControl(window);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw normal objects
		bottles.draw(MVP);
		floor.draw(MVP);
		patio.draw(MVP);
		table.draw(MVP);
		walls.draw(MVP);
		windowBG.draw(MVP);
		wood.draw(MVP);

		// Draw Transparent Objects
		doorBG.draw(MVP);
		metalObjects.draw(MVP);
		curtains.draw(MVP);

		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	// Close window and terminate glfw
	glfwTerminate();
	return 0;
}
#include "shader.hpp"
#include "loadBmp.hpp"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class PlaneMesh {
	
	std::vector<float> verts;
	std::vector<float> normals;
	std::vector<int> indices;
	glm::vec4 modelColor;
	int numVerts = 1000;
	int numIndices = 1000;
	float min;
	float max;
	GLuint waterTexID;
	GLuint heightTexID;
	GLuint programID;
	GLuint VAO;
	GLuint VBO;
	GLuint normalBufferID;

	GLuint MID;
	GLuint VID;
	GLuint MVPID;
	GLuint LightDir;
	GLuint eyeDir;
	GLuint time;
	GLuint outerTess;
	GLuint innerTess;
	GLuint modelViewProjMatrix;
	GLuint displacementTexture;

	void planeMeshQuads(float min, float max, float stepsize) {

		// The following coordinate system works as if (min, 0, min) is the origin
		// And then builds up the mesh from that origin down (in z)
		// and then to the right (in x).
		// So, one "row" of the mesh's vertices have a fixed x and increasing z
		//manually create a first column of vertices
		float x = min;
		float y = 0;
		for (float z = min; z <= max; z += stepsize) {
			verts.push_back(x);
			verts.push_back(y);
			verts.push_back(z);
			normals.push_back(0);
			normals.push_back(1);
			normals.push_back(0);
		}

		for (float x = min+stepsize; x <= max; x += stepsize) {
			for (float z = min; z <= max; z += stepsize) {
				verts.push_back(x);
				verts.push_back(y);
				verts.push_back(z);
				normals.push_back(0);
				normals.push_back(1);
				normals.push_back(0);
			}
		}

		int nCols = (max-min)/stepsize + 1;
		int i = 0, j = 0;
		for (float x = min; x < max; x += stepsize) {
			j = 0;
			for (float z = min; z < max; z += stepsize) {
				indices.push_back(i*nCols + j);
				indices.push_back(i*nCols + j + 1);
				indices.push_back((i+1)*nCols + j + 1);
				indices.push_back((i+1)*nCols + j);
				++j;
			}
			++i;
		}
	}

public:
	
	PlaneMesh(float min, float max, float stepsize) {
		this->min = min;
		this->max = max;
		modelColor = glm::vec4(0, 1.0f, 1.0f, 1.0f);

		planeMeshQuads(min, max, stepsize);
		numVerts = verts.size()/3;
		numIndices = indices.size();
		fprintf(stderr, "%d, %d\n", numVerts , numIndices);
		
		unsigned char* data;
		unsigned int width, height;

		//Bind the vertex array object
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		//Bind the vertex buffer object
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(), GL_STATIC_DRAW);

		// Enable the vertex attribute array for the vertexs 
		glEnableVertexAttribArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glVertexAttribPointer(
					0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
					3,                  // size
					GL_FLOAT,           // type
					GL_FALSE,           // normalized?
					0,                  // stride
					(void*)0            // array buffer offset
				);

		// Enable the vertex attribute array for vertex normals
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, normalBufferID);
		glVertexAttribPointer(
			1,                                // attribute 1. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		//Bind the element buffer object
		GLuint EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

		// generate buffer for normals
		glGenBuffers(1, &normalBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, normalBufferID);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);

		// load shaders 
		programID = LoadShaders("WaterShader.vertexshader", "WaterShader.geoshader", "WaterShader.fragmentshader");
		// load water texture
		loadBMP("Assets/water.bmp", &data, &width, &height);

		// generate and bind texture
		glGenTextures(1, &waterTexID);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, waterTexID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		free(data);

		// load displacment map
		loadBMP("Assets/displacement-map1.bmp", &data, &width, &height);
		// loadBMP("disp.bmp", &data, &width, &height);

		// generate and bind texture
		glGenTextures(1, &heightTexID);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, heightTexID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		// use program
		glUseProgram(programID);
		glUniform1i(glGetUniformLocation(programID, "colorTex"), 0);
		glUniform1i(glGetUniformLocation(programID, "heightTex"), 1);
		// take down program
		glUseProgram(0);


		//shaders and uniforms
		MID = glGetUniformLocation(programID, "modelMatrix");
		VID = glGetUniformLocation(programID, "viewMatrix");
		MVPID = glGetUniformLocation(programID, "projectionMatrix");
		LightDir = glGetUniformLocation(programID, "lightDirection");
		eyeDir = glGetUniformLocation(programID, "eyeDirection");
		time = glGetUniformLocation(programID, "time");
		innerTess = glGetUniformLocation(programID, "innerTess");
		outerTess = glGetUniformLocation(programID, "outerTess");

		// Set these to be something
		modelViewProjMatrix = glGetUniformLocation(programID, "modelViewProjMatrix");
		displacementTexture = glGetUniformLocation(programID, "displacementTexture");
		
		glUseProgram(programID);

		glUseProgram(0);
	}

	void draw(glm::vec3 lightPos, glm::mat4 V, glm::mat4 P) {
		glUseProgram(programID);

		// set your uniforms to be something
		glm::mat4 M = glm::mat4(1.0f);
		glm::mat4 MVP = P * V * M;
		glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(VID, 1, GL_FALSE, &V[0][0]);
		glUniformMatrix4fv(MID, 1, GL_FALSE, &M[0][0]);
		glUniform1f(innerTess,16);
		glUniform1f(outerTess,16);
		// I just put in dummy values here idk where to grab it from lol
		// but its the position of the camera so hopefully that counts for something :)
		vec3 eyeDirValue = vec3(5.0,10.0,5.0);
		glUniform3f(eyeDir, eyeDirValue.x, eyeDirValue.y, eyeDirValue.z);
		glUniform3f(LightDir, lightPos.x, lightPos.y, lightPos.z);
		glUniformMatrix4fv(modelViewProjMatrix, 1, GL_FALSE, &MVP[0][0]);
		glUniform1i(displacementTexture, 0);
		glUniform1i(displacementTexture, 1);
		
		glUniform1f(time, glfwGetTime() * 0.02);
		
		//Bind the vertex array object
		glBindVertexArray(VAO);

		//Bind the textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, waterTexID);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, heightTexID);

		//Draw the mesh
		glPatchParameteri(GL_PATCH_VERTICES, 4);
		glDrawElements(GL_PATCHES, numIndices, GL_UNSIGNED_INT, 0);

		//Clean up
		glBindVertexArray(0);
		glUseProgram(0);
	}


};

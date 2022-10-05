#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <map>
#include <vector>
#include <math.h>
#include <time.h>
#include <string>
#include <cstring>
#include <iostream>

#include "lodepng.h"
#include "shaderprogram.h"
#include "camera.h"
#include "model.h"

// Initialization and destruction
void initOpenGLProgram(GLFWwindow* window);
void freeOpenGLProgram(GLFWwindow* window);

// Callbacks
void error_callback(int error, const char* description);
void windowResizeCallback(GLFWwindow* window,int width,int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window, int* key);

// Window resolution
const int WIN_WIDTH = 1280;
const int WIN_HEIGHT = 720;

// Camera
Camera camera;
bool firstMouse = true;
float lastX = 0;
float lastY = 0;

// Light
float lightX = 25.0f;
float lightY = 0.0f;
float lightZ = 0.0f;

// Timing
float deltaTime = 0.0f;
float lastTime = 0.0f;

// Shaders
ShaderProgram *spTextured;

bool closing = false;
bool pushed = false;

enum PianoKeys {
	C=30,
	D,
	E,
	F,
	G,
	A,
	B,
	C_Sharp=96,
	D_Sharp,
	F_Sharp=99,
	G_Sharp,
	A_Sharp
};

// Drawing
void drawScene(GLFWwindow* window);



int main() {
    // Initialization operations
    GLFWwindow* window; 

	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) { 
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "OpenGL", NULL, NULL);  
	if (!window) 
	{
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); 
	glfwSwapInterval(1); 

	if (glewInit() != GLEW_OK) { 
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window);


	// Load models
	Model pianoRig("objects/piano/piano_rig.obj");
	Model pianoKlapa("objects/piano/piano_klapa.obj");
	Model pianoWhiteKey("objects/piano/piano_white_key.obj");
	Model pianoBlackKey("objects/piano/piano_black_key.obj");
	Model pianoHammer("objects/piano/piano_hammer.obj");

	Model lamp("objects/lamp/lamp.obj");
	Model cube("objects/tile/cube.obj");

	// Main loop
	int lid_pos = 0;

	int key = 200;
	int key_pos = 0;

	int floor_size = 30;
	
	while (!glfwWindowShouldClose(window)) 
	{
        // Time logic
        float currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

        // Process input
		processInput(window, &key);

        //Render
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		spTextured->use();

		glm::mat4 V = camera.GetViewMatrix();
		glm::mat4 P = glm::perspective(glm::radians(camera.fov), (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.01f, 100.0f);
		glm::mat4 M=glm::mat4(1.0f);

		glUniformMatrix4fv(glGetUniformLocation(spTextured->shaderProgram, "P"), 1, GL_FALSE, glm::value_ptr(P));
		glUniformMatrix4fv(glGetUniformLocation(spTextured->shaderProgram, "V"), 1, GL_FALSE, glm::value_ptr(V));

		
		glUniform4f(spTextured->u("lp1"), lightX, 5.0f, lightX, 1); // położenie źródła światła
		glUniform4f(spTextured->u("lp2"), lightX, 5.0f, -lightX, 1); // położenie źródła światła
		glUniform4f(spTextured->u("lp3"), -lightX, 5.0f, lightX, 1); // położenie źródła światła
		glUniform4f(spTextured->u("lp4"), -lightX, 5.0f, -lightX, 1); // położenie źródła światła
		glUniform4f(spTextured->u("lp5"), 0.0f, 7.0f, 0.0f, 1); // położenie źródła światła

		

		
		// Floor
		for(int i=floor_size; i>=-floor_size; i--)
		{
			for(int j=floor_size; j>=-floor_size; j--)
			{
				M=glm::mat4(1.0f);
				// M = glm::translate(M, glm::vec3(floor(camera.GetPosition().x), 0.0f, floor(camera.GetPosition().z)));
				M = glm::translate(M, glm::vec3(2*i, 0.0f, 2*j));
				glUniformMatrix4fv(glGetUniformLocation(spTextured->shaderProgram, "M"), 1, GL_FALSE, glm::value_ptr(M));

				cube.Draw(*spTextured);
			}
		}

		// Piano lid
		M = glm::mat4(1.0f);
		M = glm::scale(M, glm::vec3(0.2f,0.2f,0.2f));
        M = glm::rotate(M, glm::radians(180.0f), glm::vec3(0.0f,1.0f,0.0f));	

		M = glm::translate(M, glm::vec3(0.0f, lid_pos/5.0f*1.1, -lid_pos/5.0f*1.1));
		M = glm::rotate(M, glm::radians(lid_pos/5.0f), glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
		M = glm::translate(M, glm::vec3(0.0f, -lid_pos/5.0f*1.1, lid_pos/5.0f*1.1));
		glUniformMatrix4fv(glGetUniformLocation(spTextured->shaderProgram, "M"), 1, GL_FALSE, glm::value_ptr(M));
		
		pianoKlapa.Draw(*spTextured);



		// Piano rig (immovable parts)
		M = glm::mat4(1.0f);
		M = glm::scale(M, glm::vec3(0.2f,0.2f,0.2f));
        M = glm::rotate(M, glm::radians(180.0f), glm::vec3(0.0f,1.0f,0.0f));
		glUniformMatrix4fv(glGetUniformLocation(spTextured->shaderProgram, "M"), 1, GL_FALSE, glm::value_ptr(M));

		pianoRig.Draw(*spTextured);


		// Piano white keys
		
		for(int i=0; i<66; i++)
		{
			M = glm::mat4(1.0f);
            M = glm::scale(M, glm::vec3(0.2f,0.2f,0.2f));
            M = glm::rotate(M, glm::radians(180.0f), glm::vec3(0.0f,1.0f,0.0f));
			M = glm::translate(M, glm::vec3(0.0f,0.0f,i*0.85f));

			if(i==key && key < 37){
				M = glm::translate(M, glm::vec3(0.0f, key_pos/5.0f*1.1, -key_pos/5.0f*1.1));
				M = glm::rotate(M, glm::radians(key_pos/10.0f), glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)));
				M = glm::translate(M, glm::vec3(0.0f, -key_pos/5.0f*1.1, key_pos/5.0f*1.1));
			}
			
			glUniformMatrix4fv(glGetUniformLocation(spTextured->shaderProgram, "M"), 1, GL_FALSE, glm::value_ptr(M));

			pianoWhiteKey.Draw(*spTextured);
		}


		// Piano black keys
		
		for(int i=66; i<132; i++)
		{
			M = glm::mat4(1.0f);
            M = glm::scale(M, glm::vec3(0.2f,0.2f,0.2f));
            M = glm::rotate(M, glm::radians(180.0f), glm::vec3(0.0f,1.0f,0.0f));
			M = glm::translate(M, glm::vec3(0.0f,0.0f,(i-66)*0.85f));

			if(i==key && key >= 96){
				M = glm::translate(M, glm::vec3(0.0f, key_pos/5.0f*1.1, -key_pos/5.0f*1.1));
				M = glm::rotate(M, glm::radians(key_pos/10.0f), glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)));
				M = glm::translate(M, glm::vec3(0.0f, -key_pos/5.0f*1.1, key_pos/5.0f*1.1));
			}
			glUniformMatrix4fv(glGetUniformLocation(spTextured->shaderProgram, "M"), 1, GL_FALSE, glm::value_ptr(M));

			if(!((i+3)%7==0 || (i)%7==0 || i==131)) pianoBlackKey.Draw(*spTextured);
		}


		// Piano hammers
		

		for(int i=0; i<44; i++)
		{
			M = glm::mat4(1.0f);
            M = glm::scale(M, glm::vec3(0.2f,0.2f,0.2f));
            M = glm::rotate(M, glm::radians(180.0f), glm::vec3(0.0f,1.0f,0.0f));
			M = glm::translate(M, glm::vec3(0.0f,0.25f,i*1.25-1.0f));

			if(!(i<20 || i>=26) && (i==key-10 || i==key-76)){
				M = glm::translate(M, glm::vec3(0.0f, -key_pos/10.0f, 0.0f));
			}
			
			glUniformMatrix4fv(glGetUniformLocation(spTextured->shaderProgram, "M"), 1, GL_FALSE, glm::value_ptr(M));

			pianoHammer.Draw(*spTextured);
		}

		// Lamps
		M = glm::mat4(1.0f);
		M = glm::translate(M, glm::vec3(26.0f,0.0f,26.0f));
        M = glm::rotate(M, glm::radians(45.0f), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
		M = glm::scale(M, glm::vec3(0.05f,0.05f,0.05f));

		glUniformMatrix4fv(glGetUniformLocation(spTextured->shaderProgram, "M"), 1, GL_FALSE, glm::value_ptr(M));

		lamp.Draw(*spTextured);

        M = glm::mat4(1.0f);
		M = glm::translate(M, glm::vec3(26.0f,0.0f,-26.0f));
        M = glm::rotate(M, glm::radians(45.0f+90.0f), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
		M = glm::scale(M, glm::vec3(0.05f,0.05f,0.05f));

		glUniformMatrix4fv(glGetUniformLocation(spTextured->shaderProgram, "M"), 1, GL_FALSE, glm::value_ptr(M));

		lamp.Draw(*spTextured);

        M = glm::mat4(1.0f);
		M = glm::translate(M, glm::vec3(-26.0f,0.0f,-26.0f));
        M = glm::rotate(M, glm::radians(45.0f+180.0f), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
		M = glm::scale(M, glm::vec3(0.05f,0.05f,0.05f));

		glUniformMatrix4fv(glGetUniformLocation(spTextured->shaderProgram, "M"), 1, GL_FALSE, glm::value_ptr(M));

		lamp.Draw(*spTextured);

        M = glm::mat4(1.0f);
		M = glm::translate(M, glm::vec3(-26.0f,0.0f,26.0f));
        M = glm::rotate(M, glm::radians(45.0f+270.0f), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
		M = glm::scale(M, glm::vec3(0.05f,0.05f,0.05f));

		glUniformMatrix4fv(glGetUniformLocation(spTextured->shaderProgram, "M"), 1, GL_FALSE, glm::value_ptr(M));

		lamp.Draw(*spTextured);

		if(key_pos==10) { pushed=false; }
		if(pushed == true && key_pos<130) key_pos++;
		else if(pushed == false && key_pos>=0) {key_pos--; if(key_pos==0) key=200;}
		if(closing == true && lid_pos<130) lid_pos++;
		else if(closing == false && lid_pos>=0) lid_pos--;

        // Swap buffer and poll events
        glfwSwapBuffers(window);
		glfwPollEvents(); 
	}


	// Cleaning operations
    freeOpenGLProgram(window);
	exit(EXIT_SUCCESS);
}


void initOpenGLProgram(GLFWwindow* window) {
	
	glClearColor(0,0,0,1);
	glEnable(GL_DEPTH_TEST);
	glfwSetWindowSizeCallback(window,windowResizeCallback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	spTextured = new ShaderProgram("v_textured.glsl",NULL, "f_textured.glsl");
}

void freeOpenGLProgram(GLFWwindow* window) {
    
    glfwDestroyWindow(window); 
	glfwTerminate(); 
}

void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void windowResizeCallback(GLFWwindow* window,int width,int height) {
    if (height==0) return;
    glViewport(0,0,width,height);
}

void mouse_callback(GLFWwindow* window, double xpos ,double ypos)
{
	if(firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	camera.processMouseInput(xoffset, yoffset);
}

void processInput(GLFWwindow* window, int* key) {
    
	float camSpeed = 5.0*deltaTime;

	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);

	if(camera.GetPosition().y <= 25.0f && camera.GetPosition().y >  0.0f && camera.GetPosition().x <= 40.0f && camera.GetPosition().x >=-40.0f && camera.GetPosition().z <= 40.0f && camera.GetPosition().z >=-40.0f){
		if(glfwGetKey(window, GLFW_KEY_SPACE)       == GLFW_PRESS) { camera.processKeyboardInput(UP, deltaTime); }
		if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)  == GLFW_PRESS) { camera.processKeyboardInput(DOWN, deltaTime); }
		if(glfwGetKey(window, GLFW_KEY_W)           == GLFW_PRESS) { camera.processKeyboardInput(FORWARD, deltaTime); }
		if(glfwGetKey(window, GLFW_KEY_S)           == GLFW_PRESS) { camera.processKeyboardInput(BACKWARD, deltaTime); }
		if(glfwGetKey(window, GLFW_KEY_A)           == GLFW_PRESS) { camera.processKeyboardInput(LEFT, deltaTime); }
		if(glfwGetKey(window, GLFW_KEY_D)           == GLFW_PRESS) { camera.processKeyboardInput(RIGHT, deltaTime); }
	} else {
		camera.ResetPosition();
	}

	if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) lightZ -= camSpeed;
	if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) lightZ += camSpeed;
	if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) lightX -= camSpeed;
	if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) lightX += camSpeed;
	if(glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) lightY += camSpeed;
	if(glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) lightY -= camSpeed;

	if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {*key = C; pushed = true; }
	if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {*key = D; pushed = true; }
	if(glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {*key = E; pushed = true; }
	if(glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {*key = F; pushed = true; }
	if(glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {*key = G; pushed = true; }
	if(glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {*key = A; pushed = true; }
	if(glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {*key = B; pushed = true; }
	if(glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {*key = C_Sharp; pushed = true; }
	if(glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {*key = D_Sharp; pushed = true; }
	if(glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS) {*key = F_Sharp; pushed = true; }
	if(glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS) {*key = G_Sharp; pushed = true; }
	if(glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS) {*key = A_Sharp; pushed = true; }
	if(glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) closing = true;
	if(glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) closing = false;

}
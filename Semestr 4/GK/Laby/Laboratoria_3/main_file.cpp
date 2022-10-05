/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "constants.h"
#include "allmodels.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "myCube.h"

float speed_x = 0;//[radiany/s]
float speed_y = 0;//[radiany/s]
GLuint tex;

//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void key_callback(
	GLFWwindow* window,
	int key,
	int scancode,
	int action,
	int mod
) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT) {
			speed_y = -PI;
		}
		if (key == GLFW_KEY_RIGHT) {
			speed_y = PI;
		}
		if (key == GLFW_KEY_UP) {
			speed_x = -PI;
		}
		if (key == GLFW_KEY_DOWN) {
			speed_x = PI;
		}
		if (key == GLFW_KEY_W) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		}
		if (key == GLFW_KEY_A) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		}
		if (key == GLFW_KEY_S) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		}
		if (key == GLFW_KEY_D) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		}
	}
	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT) {
			speed_y = 0;
		}
		if (key == GLFW_KEY_UP || key == GLFW_KEY_DOWN) {
			speed_x = 0;
		}
	}
}

GLuint readTexture(char* filename){
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);

	// Wczytanie do pamięci komputera
	std::vector<unsigned char> image;
	unsigned width, height;
	unsigned error = lodepng::decode(image, width, height, filename);

	// Import do pamięci karty graficznej
	glGenTextures(1,&tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	// Wczytaj do pamięci karty graficznej skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) image.data());
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	return tex;
}


//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
    initShaders();
	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
	glClearColor(0, 0, 0, 1); //Ustaw kolor czyszczenia bufora kolorów
	glEnable(GL_DEPTH_TEST); //Włącz test głębokości na pikselach
	glfwSetKeyCallback(window, key_callback);
	tex=readTexture("stone-wall.png");
}


//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
    freeShaders();
    //************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************
	glDeleteTextures(1,&tex);
}



void przyklad1(float angle_x, float angle_y){
	
	float verts[] = {
		0, 1,0,1,
	   -1,-1,0,1,
		1,-1,0,1
	};
	int vertexCount = 3;
		
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::rotate(M, angle_y, glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::rotate(M, angle_x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 V = glm::lookAt(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //Wylicz macierz widoku
	glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f);

	spConstant->use();
	glUniformMatrix4fv(spConstant->u("P"),1,false,glm::value_ptr(P));
	glUniformMatrix4fv(spConstant->u("V"),1,false,glm::value_ptr(V));
	glUniformMatrix4fv(spConstant->u("M"),1,false,glm::value_ptr(M));
	glUniform4f(spConstant->u("color"), 1,0,0,1);

	glEnableVertexAttribArray(spConstant->a("vertex"));
	glVertexAttribPointer(spConstant->a("vertex"),4,GL_FLOAT, false, 0, verts);

	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	glDisableVertexAttribArray(spConstant->a("vertex"));
}

void przyklad2(float angle_x, float angle_y){
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::rotate(M, angle_y, glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::rotate(M, angle_x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 V = glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //Wylicz macierz widoku
	glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f);

	float verts[]={
		0,4.08,0,1,     0,0,2.88,1,    -2.5,0,-1.44,1,
		0,4.08,0,1,     0,0,2.88,1,     2.5,0,-1.44,1,
		0,4.08,0,1,     2.5,0,-1.44,1, -2.5,0,-1.44,1,
		2.5,0,-1.44,1, -2.5,0,-1.44,1,  0,0,2.88,1};
	float colors[]={
		1,0,0,1,  1,0,0,1,  1,0,0,1,
		0,1,0,1,  0,1,0,1,  0,1,0,1,
		0,0,1,1,  0,0,1,1,  0,0,1,1,
		1,1,0,1,  1,1,0,1,  1,1,0,1};
	int vertexCount=12;

	spColored->use();
	glUniformMatrix4fv(spColored->u("P"),1,false,glm::value_ptr(P));
	glUniformMatrix4fv(spColored->u("V"),1,false,glm::value_ptr(V));
	glUniformMatrix4fv(spColored->u("M"),1,false,glm::value_ptr(M));

	glEnableVertexAttribArray(spColored->a("vertex"));
	glVertexAttribPointer(spColored->a("vertex"),4,GL_FLOAT,false,0,verts);

	glEnableVertexAttribArray(spColored->a("color"));
	glVertexAttribPointer(spColored->a("color"),4,GL_FLOAT,false,0,colors);

	glDrawArrays( GL_TRIANGLES, 0, vertexCount );

	glDisableVertexAttribArray(spColored->a("vertex"));
	glDisableVertexAttribArray(spColored->a("color"));
}

void przyklad3(float angle_x, float angle_y){
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::rotate(M, angle_y, glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::rotate(M, angle_x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 V = glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //Wylicz macierz widoku
	glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f);

	float verts[]={
		0,4.08,0,1,     0,0,2.88,1,    -2.5,0,-1.44,1,    2.5,0,-1.44,1
	};
	float colors[]={
		1,0,0,1,  0,1,0,1,  0,0,1,1,  1,1,0,1
	};
	unsigned int indexes[]={
		0,1,2,  0,1,3,  0,2,3,  1,2,3
	};
	int indexCount=12;
	int vertexCount=4;

	spColored->use();
	glUniformMatrix4fv(spColored->u("P"),1,false,glm::value_ptr(P));
	glUniformMatrix4fv(spColored->u("V"),1,false,glm::value_ptr(V));
	glUniformMatrix4fv(spColored->u("M"),1,false,glm::value_ptr(M));

	glEnableVertexAttribArray(spColored->a("vertex"));
	glVertexAttribPointer(spColored->a("vertex"),4,GL_FLOAT,false,0,verts);

	glEnableVertexAttribArray(spColored->a("color"));
	glVertexAttribPointer(spColored->a("color"),4,GL_FLOAT,false,0,colors);

	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, indexes);

	glDisableVertexAttribArray(spColored->a("vertex"));
	glDisableVertexAttribArray(spColored->a("color"));
}

void cwPtaszor(float angle_x, float angle_y){
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::rotate(M, angle_y, glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::rotate(M, angle_x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 V = glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //Wylicz macierz widoku
	glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f);

	float verts[]={
		0,1.0,1.0,1,     0,1.0,-1.0,1,    1.0,0,0,1,    -1.0,0,0,1
	};
	float colors[]={
		1,0,0,1,  0,1,0,1
	};
	unsigned int indexes[]={
		0,1,2,  0,1,3
	};
	int indexCount=6;
	int vertexCount=4;

	spColored->use();
	glUniformMatrix4fv(spColored->u("P"),1,false,glm::value_ptr(P));
	glUniformMatrix4fv(spColored->u("V"),1,false,glm::value_ptr(V));
	glUniformMatrix4fv(spColored->u("M"),1,false,glm::value_ptr(M));

	glEnableVertexAttribArray(spColored->a("vertex"));
	glVertexAttribPointer(spColored->a("vertex"),4,GL_FLOAT,false,0,verts);

	glEnableVertexAttribArray(spColored->a("color"));
	glVertexAttribPointer(spColored->a("color"),4,GL_FLOAT,false,0,colors);

	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, indexes);

	glDisableVertexAttribArray(spColored->a("vertex"));
	glDisableVertexAttribArray(spColored->a("color"));
}

void cwKostka(float angle_x, float angle_y){
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::rotate(M, angle_y, glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::rotate(M, angle_x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 V = glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //Wylicz macierz widoku
	glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f);

	spColored->use();
	glUniformMatrix4fv(spColored->u("P"),1,false,glm::value_ptr(P));
	glUniformMatrix4fv(spColored->u("V"),1,false,glm::value_ptr(V));
	glUniformMatrix4fv(spColored->u("M"),1,false,glm::value_ptr(M));

	glEnableVertexAttribArray(spColored->a("vertex"));
	glVertexAttribPointer(spColored->a("vertex"),4,GL_FLOAT,false,0,myCubeVertices);

	glEnableVertexAttribArray(spColored->a("color"));
	glVertexAttribPointer(spColored->a("color"),4,GL_FLOAT,false,0,myCubeColors);

	glDrawArrays(GL_TRIANGLES, 0, myCubeVertexCount);

	glDisableVertexAttribArray(spColored->a("vertex"));
	glDisableVertexAttribArray(spColored->a("color"));
}

void cwTekstura1(float angle_x, float angle_y)
{
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::rotate(M, angle_y, glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::rotate(M, angle_x, glm::vec3(1.0f, 0.0f, 0.0f));
	M = glm::scale(M, glm::vec3(2.0f, 2.0f, 2.0f));
	glm::mat4 V = glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //Wylicz macierz widoku
	glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f);

	//Tablica współrzędnych wierzchołków
	float verts[]={
		//ściana 1
		1.0f,-1.0f,-1.0f,1.0f,
		-1.0f, 1.0f,-1.0f,1.0f,
		-1.0f,-1.0f,-1.0f,1.0f,

		1.0f,-1.0f,-1.0f,1.0f,
		1.0f, 1.0f,-1.0f,1.0f,
		-1.0f, 1.0f,-1.0f,1.0f,

		//ściana 2
		-1.0f,-1.0f, 1.0f,1.0f,
		1.0f, 1.0f, 1.0f,1.0f,
		1.0f,-1.0f, 1.0f,1.0f,

		-1.0f,-1.0f, 1.0f,1.0f,
		-1.0f, 1.0f, 1.0f,1.0f,
		1.0f, 1.0f, 1.0f,1.0f,


		//ściana 3
		-1.0f,-1.0f,-1.0f,1.0f,
		1.0f,-1.0f, 1.0f,1.0f,
		1.0f,-1.0f,-1.0f,1.0f,

		-1.0f,-1.0f,-1.0f,1.0f,
		-1.0f,-1.0f, 1.0f,1.0f,
		1.0f,-1.0f, 1.0f,1.0f,

		//ściana 4
		-1.0f, 1.0f, 1.0f,1.0f,
		1.0f, 1.0f,-1.0f,1.0f,
		1.0f, 1.0f, 1.0f,1.0f,

		-1.0f, 1.0f, 1.0f,1.0f,
		-1.0f, 1.0f,-1.0f,1.0f,
		1.0f, 1.0f,-1.0f,1.0f,

		//ściana 5
		-1.0f,-1.0f,-1.0f,1.0f,
		-1.0f, 1.0f, 1.0f,1.0f,
		-1.0f,-1.0f, 1.0f,1.0f,

		-1.0f,-1.0f,-1.0f,1.0f,
		-1.0f, 1.0f,-1.0f,1.0f,
		-1.0f, 1.0f, 1.0f,1.0f,

		//ściana 6
		1.0f,-1.0f, 1.0f,1.0f,
		1.0f, 1.0f,-1.0f,1.0f,
		1.0f,-1.0f,-1.0f,1.0f,

		1.0f,-1.0f, 1.0f,1.0f,
		1.0f, 1.0f, 1.0f,1.0f,
		1.0f, 1.0f,-1.0f,1.0f,
	};

	//Tablica współrzędnych teksturowania
	float texCoords[]={
		// Ściana 1
		5.0f, 0.0f,	   //A
		0.0f, 5.0f,    //B
		0.0f, 0.0f,    //C

		5.0f, 0.0f,    //A
		5.0f, 5.0f,    //D
		0.0f, 5.0f,    //B

		// Ściana 2
		5.0f, 0.0f,	//A
		0.0f, 5.0f,    //B
		0.0f, 0.0f,    //C

		5.0f, 0.0f,    //A
		5.0f, 5.0f,    //D
		0.0f, 5.0f,    //B

		// Ściana 3
		5.0f, 0.0f,	//A
		0.0f, 5.0f,    //B
		0.0f, 0.0f,    //C

		5.0f, 0.0f,    //A
		5.0f, 5.0f,    //D
		0.0f, 5.0f,    //B

		// Ściana 4
		5.0f, 0.0f,	//A
		0.0f, 5.0f,    //B
		0.0f, 0.0f,    //C

		5.0f, 0.0f,    //A
		5.0f, 5.0f,    //D
		0.0f, 5.0f,    //B

		// Ściana 5
		5.0f, 0.0f,	//A
		0.0f, 5.0f,    //B
		0.0f, 0.0f,    //C

		5.0f, 0.0f,    //A
		5.0f, 5.0f,    //D
		0.0f, 5.0f,    //B

		// Ściana 6
		5.0f, 0.0f,	//A
		0.0f, 5.0f,    //B
		0.0f, 0.0f,    //C

		5.0f, 0.0f,    //A
		5.0f, 5.0f,    //D
		0.0f, 5.0f,    //B
	};

	//Liczba wierzchołków w tablicy
	int vertexCount=36;

	spTextured->use();
	glUniformMatrix4fv(spTextured->u("P"),1,false,glm::value_ptr(P));
	glUniformMatrix4fv(spTextured->u("V"),1,false,glm::value_ptr(V));
	glUniformMatrix4fv(spTextured->u("M"),1,false,glm::value_ptr(M));

	glEnableVertexAttribArray(spTextured->a("vertex"));
	glVertexAttribPointer(spTextured->a("vertex"),4,GL_FLOAT,false,0,verts);

	glEnableVertexAttribArray(spTextured->a("texCoord"));
	glVertexAttribPointer(spTextured->a("texCoord"),2,GL_FLOAT,false,0,texCoords);

	glActiveTexture(GL_TEXTURE0); 
	glBindTexture(GL_TEXTURE_2D,tex);
	glUniform1i(spTextured->u("tex"),0);

	glDrawArrays( GL_TRIANGLES, 0, vertexCount );

	glDisableVertexAttribArray(spTextured->a("vertex"));
	glDisableVertexAttribArray(spTextured->a("texCoord"));
}

void cwTekstura2(float angle_x, float angle_y)
{
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::rotate(M, angle_y, glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::rotate(M, angle_x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 V = glm::lookAt(glm::vec3(0.0f, 1.5f, -1.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //Wylicz macierz widoku
	glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 0.01f, 50.0f);

	//Tablica współrzędnych wierzchołków
	float verts[]={
		//ściana 1
		1.0f,-1.0f,-1.0f,1.0f,
		-1.0f, 1.0f,-1.0f,1.0f,
		-1.0f,-1.0f,-1.0f,1.0f,

		1.0f,-1.0f,-1.0f,1.0f,
		1.0f, 1.0f,-1.0f,1.0f,
		-1.0f, 1.0f,-1.0f,1.0f,

		//ściana 2
		-1.0f,-1.0f, 1.0f,1.0f,
		1.0f, 1.0f, 1.0f,1.0f,
		1.0f,-1.0f, 1.0f,1.0f,

		-1.0f,-1.0f, 1.0f,1.0f,
		-1.0f, 1.0f, 1.0f,1.0f,
		1.0f, 1.0f, 1.0f,1.0f,


		//ściana 3
		-1.0f,-1.0f,-1.0f,1.0f,
		1.0f,-1.0f, 1.0f,1.0f,
		1.0f,-1.0f,-1.0f,1.0f,

		-1.0f,-1.0f,-1.0f,1.0f,
		-1.0f,-1.0f, 1.0f,1.0f,
		1.0f,-1.0f, 1.0f,1.0f,

		//ściana 4
		-1.0f, 1.0f, 1.0f,1.0f,
		1.0f, 1.0f,-1.0f,1.0f,
		1.0f, 1.0f, 1.0f,1.0f,

		-1.0f, 1.0f, 1.0f,1.0f,
		-1.0f, 1.0f,-1.0f,1.0f,
		1.0f, 1.0f,-1.0f,1.0f,

		//ściana 5
		-1.0f,-1.0f,-1.0f,1.0f,
		-1.0f, 1.0f, 1.0f,1.0f,
		-1.0f,-1.0f, 1.0f,1.0f,

		-1.0f,-1.0f,-1.0f,1.0f,
		-1.0f, 1.0f,-1.0f,1.0f,
		-1.0f, 1.0f, 1.0f,1.0f,

		//ściana 6
		1.0f,-1.0f, 1.0f,1.0f,
		1.0f, 1.0f,-1.0f,1.0f,
		1.0f,-1.0f,-1.0f,1.0f,

		1.0f,-1.0f, 1.0f,1.0f,
		1.0f, 1.0f, 1.0f,1.0f,
		1.0f, 1.0f,-1.0f,1.0f,
	};

	//Tablica współrzędnych teksturowania
	float texCoords[]={
		// Ściana 1
		20.0f, 0.0f,	   //A
		0.0f, 20.0f,    //B
		0.0f, 0.0f,    //C

		20.0f, 0.0f,    //A
		20.0f, 20.0f,    //D
		0.0f, 20.0f,    //B

		// Ściana 2
		20.0f, 0.0f,	//A
		0.0f, 20.0f,    //B
		0.0f, 0.0f,    //C

		20.0f, 0.0f,    //A
		20.0f, 20.0f,    //D
		0.0f, 20.0f,    //B

		// Ściana 3
		20.0f, 0.0f,	//A
		0.0f, 20.0f,    //B
		0.0f, 0.0f,    //C

		20.0f, 0.0f,    //A
		20.0f, 20.0f,    //D
		0.0f, 20.0f,    //B

		// Ściana 4
		20.0f, 0.0f,	//A
		0.0f, 20.0f,    //B
		0.0f, 0.0f,    //C

		20.0f, 0.0f,    //A
		20.0f, 20.0f,    //D
		0.0f, 20.0f,    //B

		// Ściana 5
		20.0f, 0.0f,	//A
		0.0f, 20.0f,    //B
		0.0f, 0.0f,    //C

		20.0f, 0.0f,    //A
		20.0f, 20.0f,    //D
		0.0f, 20.0f,    //B

		// Ściana 6
		20.0f, 0.0f,	//A
		0.0f, 20.0f,    //B
		0.0f, 0.0f,    //C

		20.0f, 0.0f,    //A
		20.0f, 20.0f,    //D
		0.0f, 20.0f,    //B
	};

	//Liczba wierzchołków w tablicy
	int vertexCount=36;

	spTextured->use();
	glUniformMatrix4fv(spTextured->u("P"),1,false,glm::value_ptr(P));
	glUniformMatrix4fv(spTextured->u("V"),1,false,glm::value_ptr(V));
	glUniformMatrix4fv(spTextured->u("M"),1,false,glm::value_ptr(M));

	glEnableVertexAttribArray(spTextured->a("vertex"));
	glVertexAttribPointer(spTextured->a("vertex"),4,GL_FLOAT,false,0,verts);

	glEnableVertexAttribArray(spTextured->a("texCoord"));
	glVertexAttribPointer(spTextured->a("texCoord"),2,GL_FLOAT,false,0,texCoords);

	glActiveTexture(GL_TEXTURE0); 
	glBindTexture(GL_TEXTURE_2D,tex);
	glUniform1i(spTextured->u("tex"),0);

	glDrawArrays( GL_TRIANGLES, 18, 6 );

	glDisableVertexAttribArray(spTextured->a("vertex"));
	glDisableVertexAttribArray(spTextured->a("texCoord"));
}

void cwTekstura3(float angle_x, float angle_y)
{
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::rotate(M, angle_y, glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::rotate(M, angle_x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 V = glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //Wylicz macierz widoku
	glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f);

	//Tablica współrzędnych wierzchołków
	float verts[]={
		//ściana 1
		1.0f,-1.0f,-1.0f,1.0f,
		-1.0f, 1.0f,-1.0f,1.0f,
		-1.0f,-1.0f,-1.0f,1.0f,

		1.0f,-1.0f,-1.0f,1.0f,
		1.0f, 1.0f,-1.0f,1.0f,
		-1.0f, 1.0f,-1.0f,1.0f,

		//ściana 2
		-1.0f,-1.0f, 1.0f,1.0f,
		1.0f, 1.0f, 1.0f,1.0f,
		1.0f,-1.0f, 1.0f,1.0f,

		-1.0f,-1.0f, 1.0f,1.0f,
		-1.0f, 1.0f, 1.0f,1.0f,
		1.0f, 1.0f, 1.0f,1.0f,


		//ściana 3
		-1.0f,-1.0f,-1.0f,1.0f,
		1.0f,-1.0f, 1.0f,1.0f,
		1.0f,-1.0f,-1.0f,1.0f,

		-1.0f,-1.0f,-1.0f,1.0f,
		-1.0f,-1.0f, 1.0f,1.0f,
		1.0f,-1.0f, 1.0f,1.0f,

		//ściana 4
		-1.0f, 1.0f, 1.0f,1.0f,
		1.0f, 1.0f,-1.0f,1.0f,
		1.0f, 1.0f, 1.0f,1.0f,

		-1.0f, 1.0f, 1.0f,1.0f,
		-1.0f, 1.0f,-1.0f,1.0f,
		1.0f, 1.0f,-1.0f,1.0f,

		//ściana 5
		-1.0f,-1.0f,-1.0f,1.0f,
		-1.0f, 1.0f, 1.0f,1.0f,
		-1.0f,-1.0f, 1.0f,1.0f,

		-1.0f,-1.0f,-1.0f,1.0f,
		-1.0f, 1.0f,-1.0f,1.0f,
		-1.0f, 1.0f, 1.0f,1.0f,

		//ściana 6
		1.0f,-1.0f, 1.0f,1.0f,
		1.0f, 1.0f,-1.0f,1.0f,
		1.0f,-1.0f,-1.0f,1.0f,

		1.0f,-1.0f, 1.0f,1.0f,
		1.0f, 1.0f, 1.0f,1.0f,
		1.0f, 1.0f,-1.0f,1.0f
	};

	//Tablica współrzędnych teksturowania
	float texCoords[]={
		// Ściana 1
		1.0f, 0.0f,	   //A
		0.0f, 1.0f,    //B
		0.0f, 0.0f,    //C

		1.0f, 0.0f,    //A
		1.0f, 1.0f,    //D
		0.0f, 1.0f,    //B

		// Ściana 2
		1.0f, 0.0f,	//A
		0.0f, 1.0f,    //B
		0.0f, 0.0f,    //C

		1.0f, 0.0f,    //A
		1.0f, 1.0f,    //D
		0.0f, 1.0f,    //B

		// Ściana 3
		1.0f, 0.0f,	//A
		0.0f, 1.0f,    //B
		0.0f, 0.0f,    //C

		1.0f, 0.0f,    //A
		1.0f, 1.0f,    //D
		0.0f, 1.0f,    //B

		// Ściana 4
		1.0f, 0.0f,	//A
		0.0f, 1.0f,    //B
		0.0f, 0.0f,    //C

		1.0f, 0.0f,    //A
		1.0f, 1.0f,    //D
		0.0f, 1.0f,    //B

		// Ściana 5
		1.0f, 0.0f,	//A
		0.0f, 1.0f,    //B
		0.0f, 0.0f,    //C

		1.0f, 0.0f,    //A
		1.0f, 1.0f,    //D
		0.0f, 1.0f,    //B

		// Ściana 6
		1.0f, 0.0f,	//A
		0.0f, 1.0f,    //B
		0.0f, 0.0f,    //C

		1.0f, 0.0f,    //A
		1.0f, 1.0f,    //D
		0.0f, 1.0f    //B
	};

	//Tablica wektorów normalnych
	float normals[]={
		// 1
		0.0f,0.0f,-1.0f,0.0f, //A
		0.0f,0.0f,-1.0f,0.0f, //B
		0.0f,0.0f,-1.0f,0.0f, //C

		0.0f,0.0f,-1.0f,0.0f, //A
		0.0f,0.0f,-1.0f,0.0f, //D
		0.0f,0.0f,-1.0f,0.0f, //B

		// 2
		0.0f,0.0f,1.0f,0.0f, //A
		0.0f,0.0f,1.0f,0.0f, //B
		0.0f,0.0f,1.0f,0.0f, //C

		0.0f,0.0f,1.0f,0.0f, //A
		0.0f,0.0f,1.0f,0.0f, //D
		0.0f,0.0f,1.0f,0.0f, //B

		// 3
		0.0f,-1.0f,0.0f,0.0f, //A
		0.0f,-1.0f,0.0f,0.0f, //B
		0.0f,-1.0f,0.0f,0.0f, //C

		0.0f,-1.0f,0.0f,0.0f, //A
		0.0f,-1.0f,0.0f,0.0f, //D
		0.0f,-1.0f,0.0f,0.0f, //B

		// 4
		0.0f,1.0f,0.0f,0.0f, //A
		0.0f,1.0f,0.0f,0.0f, //B
		0.0f,1.0f,0.0f,0.0f, //C

		0.0f,1.0f,0.0f,0.0f, //A
		0.0f,1.0f,0.0f,0.0f, //D
		0.0f,1.0f,0.0f,0.0f, //B

		// 5
		-1.0f,0.0f,0.0f,0.0f, //A
		-1.0f,0.0f,0.0f,0.0f, //B
		-1.0f,0.0f,0.0f,0.0f, //C

		-1.0f,0.0f,0.0f,0.0f, //A
		-1.0f,0.0f,0.0f,0.0f, //D
		-1.0f,0.0f,0.0f,0.0f, //B

		// 6
		1.0f,0.0f,1.0f,0.0f, //A
		1.0f,0.0f,1.0f,0.0f, //B
		1.0f,0.0f,1.0f,0.0f, //C

		1.0f,0.0f,1.0f,0.0f, //A
		1.0f,0.0f,1.0f,0.0f, //D
		1.0f,0.0f,1.0f,0.0f //B
	};

	//Liczba wierzchołków w tablicy
	int vertexCount=36;

	spLambertTextured->use();
	glUniformMatrix4fv(spLambertTextured->u("P"),1,false,glm::value_ptr(P));
	glUniformMatrix4fv(spLambertTextured->u("V"),1,false,glm::value_ptr(V));
	glUniformMatrix4fv(spLambertTextured->u("M"),1,false,glm::value_ptr(M));

	glEnableVertexAttribArray(spLambertTextured->a("vertex"));
	glVertexAttribPointer(spLambertTextured->a("vertex"),4,GL_FLOAT,false,0,verts);

	glEnableVertexAttribArray(spLambertTextured->a("normal"));
	glVertexAttribPointer(spLambertTextured->a("normal"),4,GL_FLOAT,false,0,normals);

	glEnableVertexAttribArray(spLambertTextured->a("texCoord"));
	glVertexAttribPointer(spLambertTextured->a("texCoord"),2,GL_FLOAT,false,0,texCoords);

	glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D,tex);
	glUniform1i(spLambertTextured->u("tex"),0);

	glDrawArrays( GL_TRIANGLES, 0, vertexCount );

	glDisableVertexAttribArray(spLambertTextured->a("vertex"));
	glDisableVertexAttribArray(spLambertTextured->a("normal"));
	glDisableVertexAttribArray(spLambertTextured->a("texCoord"));
}

//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window,float angle_x,float angle_y) {
	//************Tutaj umieszczaj kod rysujący obraz******************l
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wyczyść bufor koloru i bufor głębokości
	
	glm::mat4 M = glm::mat4(1.0f); //Zainicjuj macierz modelu macierzą jednostkową
	M = glm::rotate(M, angle_y, glm::vec3(0.0f, 1.0f, 0.0f)); //Pomnóż macierz modelu razy macierz obrotu o kąt angle wokół osi Y
	M = glm::rotate(M, angle_x, glm::vec3(1.0f, 0.0f, 0.0f)); //Pomnóż macierz modelu razy macierz obrotu o kąt angle wokół osi X
	glm::mat4 V = glm::lookAt(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //Wylicz macierz widoku
	glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f); //Wylicz macierz rzutowania

	// //Zamiast poniższych linijek należy wstawić kod dotyczący rysowania własnych obiektów (glDrawArrays/glDrawElements i wszystko dookoła)
	// //-----------
	// spLambert->use(); //Aktywuj program cieniujący
	// glUniform4f(spLambert->u("color"), 0, 1, 0, 1); //Ustaw kolor rysowania obiektu
	// glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(P)); //Załaduj do programu cieniującego macierz rzutowania
	// glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(V)); //Załaduj do programu cieniującego macierz widoku
	// glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(M)); //Załaduj do programu cieniującego macierz modelu
	
	// Models::cube.drawSolid(); //Narysuj obiekt
	// //-----------

	// przyklad1(angle_x, angle_y);
	// przyklad2(angle_x, angle_y);
	// przyklad3(angle_x, angle_y);

	// cwPtaszor(angle_x, angle_y);
	// cwKostka(angle_x, angle_y);
	cwTekstura1(angle_x, angle_y);
	// cwTekstura2(angle_x, angle_y);
	// cwTekstura3(angle_x, angle_y);


	glfwSwapBuffers(window); //Skopiuj bufor tylny do bufora przedniego
}


int main(void)
{
	GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
	{
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekę GLEW
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjujące

	//Główna pętla
	float angle_x = 0; //zadeklaruj zmienną przechowującą aktualny kąt obrotu
	float angle_y = 0; //zadeklaruj zmienną przechowującą aktualny kąt obrotu
	glfwSetTime(0); //Wyzeruj licznik czasu
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
		angle_x += speed_x * glfwGetTime(); //Oblicz kąt o jaki obiekt obrócił się podczas poprzedniej klatki
		angle_y += speed_y * glfwGetTime(); //Oblicz kąt o jaki obiekt obrócił się podczas poprzedniej klatki
		glfwSetTime(0); //Wyzeruj licznik czasu
		drawScene(window,angle_x,angle_y); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}

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
#include "constants.h"
#include "allmodels.h"
#include "lodepng.h"
#include "shaderprogram.h"

//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
    initShaders();
	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}


//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
    freeShaders();
    //************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************
}

void cwPlanety(float angle)
{
	glm::mat4 V = glm::lookAt(
		glm::vec3(0.0f, 0.0f, -5.0f),
		glm::vec3(0.0f, 0.0f,  0.0f),
		glm::vec3(0.0f, 1.0f,  0.0f)
	);
	glm::mat4 P = glm::perspective(50.0f*PI/180.0f, 1.0f, 1.0f, 50.0f);

	spLambert->use();
	glUniformMatrix4fv(spLambert->u("P"),1,false,glm::value_ptr(P));
	glUniformMatrix4fv(spLambert->u("V"),1,false,glm::value_ptr(V));

	// Sun
	glm::mat4 M;

	M = glm::mat4(1.0f);
	M = glm::translate(M, glm::vec3(0.0f, 0.0f, 0.0f));
	M = glm::rotate(M, angle*0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::scale(M, glm::vec3(0.5, 0.5, 0.5));
	
	glUniformMatrix4fv(spLambert->u("M"),1,false,glm::value_ptr(M));
	glUniform4f(spLambert->u("color"), 1.0, 0.84, 0.0, 1.0);
	Models::sphere.drawSolid();	

	// Earth
	M = glm::mat4(1.0f);

	M = glm::rotate(M, angle, glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::translate(M, glm::vec3(1.5f, 0.0f, 0.0f));
	M = glm::rotate(M, angle, glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::scale(M, glm::vec3(0.2f, 0.2f, 0.2f));
	
	glUniformMatrix4fv(spLambert->u("M"),1,false,glm::value_ptr(M));
	glUniform4f(spLambert->u("color"), 0.0, 0.84, 1.0, 1.0);
	Models::sphere.drawSolid();

	// Moon
	M = glm::mat4(1.0f);

	M = glm::rotate(M, angle, glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::translate(M, glm::vec3(1.5f, 0.0f, 0.0f));
	M = glm::rotate(M, angle, glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::translate(M, glm::vec3(0.5f, 0.0f, 0.0f));
	M = glm::scale(M, glm::vec3(0.1f, 0.1f, 0.1f));
	
	glUniformMatrix4fv(spLambert->u("M"),1,false,glm::value_ptr(M));
	glUniform4f(spLambert->u("color"), 0.375, 0.375, 0.375, 1.0);
	Models::sphere.drawSolid();


	// Mars
	M = glm::mat4(1.0f);

	M = glm::rotate(M, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	M = glm::translate(M, glm::vec3(2.0f, 0.0f, 0.0f));
	M = glm::rotate(M, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	M = glm::scale(M, glm::vec3(0.25f, 0.25f, 0.25f));
	
	glUniformMatrix4fv(spLambert->u("M"),1,false,glm::value_ptr(M));
	glUniform4f(spLambert->u("color"), 188.0f/256.0f, 39.0f/256.0f, 50.0f/256.0f, 1.0);
	Models::sphere.drawSolid();

	// Phobos
	M = glm::mat4(1.0f);

	M = glm::rotate(M, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	M = glm::translate(M, glm::vec3(2.0f, 0.0f, 0.0f));
	M = glm::rotate(M, angle, glm::vec3(1.0f, 0.0f, 0.0f));
	M = glm::translate(M, glm::vec3(0.0f, 0.0f, 0.3f));
	M = glm::scale(M, glm::vec3(0.07f, 0.07f, 0.07f));
	
	glUniformMatrix4fv(spLambert->u("M"),1,false,glm::value_ptr(M));
	glUniform4f(spLambert->u("color"), 0.375, 0.375, 0.375, 1.0);
	Models::sphere.drawSolid();
}

void cwZebatki(float angle)
{
	glm::mat4 V = glm::lookAt(
		glm::vec3(0.0f, 0.0f, -5.0f),
		glm::vec3(0.0f, 0.0f,  0.0f),
		glm::vec3(0.0f, 1.0f,  0.0f)
	);
	glm::mat4 P = glm::perspective(50.0f*PI/180.0f, 1.0f, 1.0f, 50.0f);

	spLambert->use();
	glUniformMatrix4fv(spLambert->u("P"),1,false,glm::value_ptr(P));
	glUniformMatrix4fv(spLambert->u("V"),1,false,glm::value_ptr(V));


	glm::mat4 M;

	M = glm::mat4(1.0f);
	M = glm::translate(M, glm::vec3(1.05f, 0.0f, 0.0f));
	M = glm::rotate(M, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	M = glm::scale(M, glm::vec3(1.0, 1.0, 1.0));
	
	glUniformMatrix4fv(spLambert->u("M"),1,false,glm::value_ptr(M));
	glUniform4f(spLambert->u("color"), 1.0, 0.84, 0.0, 1.0);
	Models::torus.drawSolid();

	for(int i=0; i<12; i++)
	{
		M = glm::mat4(1.0f);
		M = glm::translate(M, glm::vec3(1.05f, 0.0f, 0.0f));
		M = glm::rotate(M, 30.0f*i*PI/180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		M = glm::rotate(M, angle, glm::vec3(0.0f, 0.0f, 1.0f));
		M = glm::translate(M, glm::vec3(1.0f, 0.0f, 0.0f));
		M = glm::scale(M, glm::vec3(0.1, 0.1, 0.1));
		
		glUniformMatrix4fv(spLambert->u("M"),1,false,glm::value_ptr(M));
		glUniform4f(spLambert->u("color"), 1.0, 0.84, 0.0, 1.0);
		Models::cube.drawSolid();
	}


	M = glm::mat4(1.0f);
	M = glm::translate(M, glm::vec3(-1.05f, 0.0f, 0.0f));
	M = glm::rotate(M, -angle, glm::vec3(0.0f, 0.0f, 1.0f));
	M = glm::scale(M, glm::vec3(1.0, 1.0, 1.0));
	
	glUniformMatrix4fv(spLambert->u("M"),1,false,glm::value_ptr(M));
	glUniform4f(spLambert->u("color"), 1.0, 0.84, 0.0, 1.0);
	Models::torus.drawSolid();

	for(int i=0; i<12; i++)
	{
		M = glm::mat4(1.0f);
		M = glm::translate(M, glm::vec3(-1.05f, 0.0f, 0.0f));
		M = glm::rotate(M, 30.0f*i*PI/180.0f+15.0f*PI/180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		M = glm::rotate(M, -angle, glm::vec3(0.0f, 0.0f, 1.0f));
		M = glm::translate(M, glm::vec3(1.0f, 0.0f, 0.0f));
		M = glm::scale(M, glm::vec3(0.1, 0.1, 0.1));
		
		glUniformMatrix4fv(spLambert->u("M"),1,false,glm::value_ptr(M));
		glUniform4f(spLambert->u("color"), 1.0, 0.84, 0.0, 1.0);
		Models::cube.drawSolid();
	}	
}

void cwZebatki2(float angle)
{
	glm::mat4 V = glm::lookAt(
		glm::vec3(0.0f, 3.0f, -5.0f),
		glm::vec3(0.0f, 0.0f,  0.0f),
		glm::vec3(0.0f, 1.0f,  0.0f)
	);
	glm::mat4 P = glm::perspective(50.0f*PI/180.0f, 1.0f, 1.0f, 50.0f);

	spLambert->use();
	glUniformMatrix4fv(spLambert->u("P"),1,false,glm::value_ptr(P));
	glUniformMatrix4fv(spLambert->u("V"),1,false,glm::value_ptr(V));

	for(int i=0; i<6; i++)
	{
		glm::mat4 M;

		M = glm::mat4(1.0f);
		M = glm::rotate(M, 60.0f*PI*i/180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		M = glm::translate(M, glm::vec3(0.0f, 0.0f, 1.90f));
		M = glm::rotate(M, angle*(i%2), glm::vec3(0.0f, 0.0f, 1.0f));
		M = glm::scale(M, glm::vec3(1.0, 1.0, 1.0));
		
		glUniformMatrix4fv(spLambert->u("M"),1,false,glm::value_ptr(M));
		glUniform4f(spLambert->u("color"), 1.0, 0.84, 0.0, 1.0);
		Models::torus.drawSolid();

		for(int j=0; j<12; j++)
		{
			M = glm::mat4(1.0f);
			M = glm::rotate(M, 60.0f*PI*i/180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			M = glm::translate(M, glm::vec3(0.0f, 0.0f, 1.90f));
			M = glm::rotate(M, 30.0f*j*PI/180.0f + (i%2 ? 0 : 15.0f*PI/180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			M = glm::rotate(M, angle*(i%2 ? 1 : -1), glm::vec3(0.0f, 0.0f, 1.0f));
			M = glm::translate(M, glm::vec3(1.0f, 0.0f, 0.0f));
			M = glm::scale(M, glm::vec3(0.1, 0.1, 0.1));
			
			glUniformMatrix4fv(spLambert->u("M"),1,false,glm::value_ptr(M));
			glUniform4f(spLambert->u("color"), 1.0, 0.84, 0.0, 1.0);
			Models::cube.drawSolid();
		}
	}
	
}

void cwSamochod(float angle, float turn)
{
	glm::mat4 V = glm::lookAt(
		glm::vec3(0.0f, 3.0f, -10.0f),
		glm::vec3(0.0f, 0.0f,  0.0f),
		glm::vec3(0.0f, 1.0f,  0.0f)
	);
	glm::mat4 P = glm::perspective(50.0f*PI/180.0f, 1.0f, 1.0f, 50.0f);

	spLambert->use();
	glUniformMatrix4fv(spLambert->u("P"),1,false,glm::value_ptr(P));
	glUniformMatrix4fv(spLambert->u("V"),1,false,glm::value_ptr(V));

	glm::mat4 M;
	Models::Torus wheel;

	M = glm::mat4(1.0f);
	M = glm::translate(M, glm::vec3(0.0f, 0.0f, 0.0f));
	M = glm::scale(M, glm::vec3(3.0, 0.25, 2.0));
	
	glUniformMatrix4fv(spLambert->u("M"),1,false,glm::value_ptr(M));
	glUniform4f(spLambert->u("color"), 1.0, 0.84, 0.0, 1.0);
	Models::cube.drawSolid();


	M = glm::mat4(1.0f);
	M = glm::translate(M, glm::vec3(3.0f, 0.0f, 2.0f));
	M = glm::rotate(M, turn*45.0f*PI/180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::rotate(M, -angle, glm::vec3(0.0f, 0.0f, 1.0f));
	M = glm::scale(M, glm::vec3(1.0, 1.0, 1.0));
	
	glUniformMatrix4fv(spLambert->u("M"),1,false,glm::value_ptr(M));
	glUniform4f(spLambert->u("color"), 1.0, 0.84, 0.0, 1.0);
	wheel.drawSolid();


	M = glm::mat4(1.0f);
	M = glm::translate(M, glm::vec3(3.0f, 0.0f, -2.0f));
	M = glm::rotate(M, turn*45.0f*PI/180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::rotate(M, -angle, glm::vec3(0.0f, 0.0f, 1.0f));
	M = glm::scale(M, glm::vec3(1.0, 1.0, 1.0));
	
	glUniformMatrix4fv(spLambert->u("M"),1,false,glm::value_ptr(M));
	glUniform4f(spLambert->u("color"), 1.0, 0.84, 0.0, 1.0);
	wheel.drawSolid();


	M = glm::mat4(1.0f);
	M = glm::translate(M, glm::vec3(-3.0f, 0.0f, 2.0f));
	M = glm::rotate(M, -angle, glm::vec3(0.0f, 0.0f, 1.0f));
	M = glm::scale(M, glm::vec3(1.0, 1.0, 1.0));
	
	glUniformMatrix4fv(spLambert->u("M"),1,false,glm::value_ptr(M));
	glUniform4f(spLambert->u("color"), 1.0, 0.84, 0.0, 1.0);
	wheel.drawSolid();


	M = glm::mat4(1.0f);
	// M = glm::rotate(M, angle, glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::translate(M, glm::vec3(-3.0f, 0.0f, -2.0f));
	M = glm::rotate(M, -angle, glm::vec3(0.0f, 0.0f, 1.0f));
	M = glm::scale(M, glm::vec3(1.0, 1.0, 1.0));
	
	glUniformMatrix4fv(spLambert->u("M"),1,false,glm::value_ptr(M));
	glUniform4f(spLambert->u("color"), 1.0, 0.84, 0.0, 1.0);
	wheel.drawSolid();

}

void cwDlonRobota(float angle)
{
	glm::mat4 V = glm::lookAt(
		glm::vec3(0.0f, -10.0f, -20.0f),
		glm::vec3(0.0f, 0.0f,  0.0f),
		glm::vec3(0.0f, 1.0f,  0.0f)
	);
	glm::mat4 P = glm::perspective(50.0f*PI/180.0f, 1.0f, 1.0f, 50.0f);

	spLambert->use();
	glUniformMatrix4fv(spLambert->u("P"),1,false,glm::value_ptr(P));
	glUniformMatrix4fv(spLambert->u("V"),1,false,glm::value_ptr(V));


	glm::mat4 M;

	M = glm::mat4(1.0f);
	M = glm::translate(M, glm::vec3(0.0f, 0.0f, 0.0f));
	M = glm::scale(M, glm::vec3(1.0, 0.5, 1.0));
	
	glUniformMatrix4fv(spLambert->u("M"),1,false,glm::value_ptr(M));
	glUniform4f(spLambert->u("color"), 1.0, 0.84, 0.0, 1.0);
	Models::cube.drawSolid();

	for(int i=0; i<360; i+=90)
	{
		M = glm::mat4(1.0f);
		M = glm::rotate(M, i*PI/180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		M = glm::translate(M, glm::vec3(1.0f, 0.0f, 0.0f));
		M = glm::rotate(M, angle, glm::vec3(0.0f, 0.0f, 1.0f));
		M = glm::translate(M, glm::vec3(2.0f, 0.0f, 0.0f));
		M = glm::scale(M, glm::vec3(2.0, 0.5, 1.0));
		
		glUniformMatrix4fv(spLambert->u("M"),1,false,glm::value_ptr(M));
		glUniform4f(spLambert->u("color"), 1.0, 0.84, 0.0, 1.0);
		Models::cube.drawSolid();


		M = glm::mat4(1.0f);
		M = glm::rotate(M, i*PI/180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		M = glm::translate(M, glm::vec3(1.0f, 0.0f, 0.0f));
		M = glm::rotate(M, angle, glm::vec3(0.0f, 0.0f, 1.0f));
		M = glm::translate(M, glm::vec3(4.0f, 0.0f, 0.0f));
		M = glm::rotate(M, angle, glm::vec3(0.0f, 0.0f, 1.0f));
		M = glm::translate(M, glm::vec3(2.0f, 0.0f, 0.0f));
		M = glm::scale(M, glm::vec3(2.0, 0.5, 1.0));
		
		glUniformMatrix4fv(spLambert->u("M"),1,false,glm::value_ptr(M));
		glUniform4f(spLambert->u("color"), 1.0, 0.84, 0.0, 1.0);
		Models::cube.drawSolid();
	}
}

//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window, float angle, float turn) {
	//************Tutaj umieszczaj kod rysujący obraz******************

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// spConstant->use();  //Aktywacja prograamu cieniującego 1
	// glUniform4f(spConstant->u("color"), 1.0, 0.84, 0.0, 1.0);
	// glUniformMatrix4fv(spConstant->u("P"), 1, false, glm::value_ptr(P));
	// glUniformMatrix4fv(spConstant->u("V"), 1, false, glm::value_ptr(V));
	// glUniformMatrix4fv(spConstant->u("M"), 1, false, glm::value_ptr(M));

	// spLambert->use();  //Aktywacja prograamu cieniującego 2
	// glUniform4f(spLambert->u("color"), 1.0, 0.84, 0.0, 1.0);
	// glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(P));
	// glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(V));
	// glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(M));


	cwPlanety(angle);
	// cwZebatki(angle);
	// cwZebatki2(angle);
	// cwSamochod(angle, turn);
	// cwDlonRobota(angle);
				

	glfwSwapBuffers(window);
}

float wheelSpeed=0;
float angle=0;
float turn=0;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(action == GLFW_PRESS)
	{
		// if(key == GLFW_KEY_A) printf("A \n");
		// if(key == GLFW_KEY_D) printf("D \n");
		// if(key == GLFW_KEY_W && (mods & GLFW_MOD_ALT) != 0) printf("ALT+W \n");

		// if(key == GLFW_KEY_RIGHT) speed=3.14159;
		// if(key == GLFW_KEY_LEFT) speed=-3.14159;


		if(key == GLFW_KEY_UP)
		{
			wheelSpeed=3.14159;
		}
		if(key == GLFW_KEY_DOWN)
		{
			wheelSpeed=-3.14159;
		}
		if(key == GLFW_KEY_RIGHT)
		{
			turn=1;
		}
		if(key == GLFW_KEY_LEFT)
		{
			turn=-1;
		}
	}

	if(action == GLFW_RELEASE)
	{
		// if(key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT) speed=0;
		if(key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT) turn=0;
		if(key == GLFW_KEY_UP || key == GLFW_KEY_DOWN) wheelSpeed=0;
	}
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

	glfwSetTime(0);
	glfwSetKeyCallback(window, key_callback);

	//Główna pętla
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
		angle+=wheelSpeed*glfwGetTime();
		glfwSetTime(0);

		drawScene(window, angle, turn); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}

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
#define GLM_FORCE_SWIZZLE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "myCube.h"
#include "myTeapot.h"

float speed_x=0;
float speed_y=0;
float aspectRatio=1.78;


// camera
glm::vec3 camPos = glm::vec3(0.0f, 0.0f, -4.0f);
glm::vec3 camFront = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);
float yaw = -90.0f;
float pitch = 0.0f;
float fov = 45.0f;

// mouse
bool firstMouse = true;
float lastX = 0;
float lastY = 0;

float deltaTime = 0.0f;
float lastTime = 0.0f;

ShaderProgram *sp;


//Odkomentuj, żeby rysować kostkę
float* vertices = myCubeVertices;
float* normals = myCubeNormals;
float* texCoords = myCubeTexCoords;
float* colors = myCubeColors;
float* c1 = myCubeC1;
float* c2 = myCubeC2;
float* c3 = myCubeC3;
int vertexCount = myCubeVertexCount;

GLuint tex0;
GLuint tex1;

//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}


void processInput(GLFWwindow* window) {
    
	float camSpeed = 2.5*deltaTime;

	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camPos += glm::normalize(glm::cross(camUp, glm::cross(camFront, camUp))) * camSpeed;
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camPos -= glm::normalize(glm::cross(camUp, glm::cross(camFront, camUp))) * camSpeed;
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camPos -= glm::normalize(glm::cross(camFront, camUp)) * camSpeed;
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camPos += glm::normalize(glm::cross(camFront, camUp)) * camSpeed;
	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) camPos += camSpeed * camUp;
	if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) camPos -= camSpeed * camUp;
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

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if(pitch > 89.0f) pitch = 89.0f;
	if(pitch < -89.0f) pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	camFront = glm::normalize(front);
}

void windowResizeCallback(GLFWwindow* window,int width,int height) {
    if (height==0) return;
    aspectRatio=(float)width/(float)height;
    glViewport(0,0,width,height);
}

GLuint readTexture(const char* filename) {	
  GLuint tex;	
  glActiveTexture(GL_TEXTURE0); 	

  //Wczytanie do pamięci komputera
  std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
  unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
  //Wczytaj obrazek
  unsigned error = lodepng::decode(image, width, height, filename);
 
  //Import do pamięci karty graficznej
  glGenTextures(1,&tex); //Zainicjuj jeden uchwyt
  glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
  //Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
  glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
    GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) image.data());	

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	

  return tex;
}

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
	glClearColor(1,1,1,1);
	glEnable(GL_DEPTH_TEST);
	glfwSetWindowSizeCallback(window,windowResizeCallback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	sp=new ShaderProgram("v_simplest.glsl",NULL,"f_simplest.glsl");
	tex0 = readTexture("metal.png");
	tex1 = readTexture("sky.png");
}


//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
    //************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************

    delete sp;
}



//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window, glm::vec3 camPos, glm::vec3 camFront, glm::vec3 camUp) {
	//************Tutaj umieszczaj kod rysujący obraz******************l
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 V=glm::lookAt(camPos, camPos+camFront, camUp); //Wylicz macierz widoku

    glm::mat4 P=glm::perspective(glm::radians(fov), aspectRatio, 0.01f, 50.0f); //Wylicz macierz rzutowania

    glm::mat4 M=glm::mat4(1.0f);

    sp->use();//Aktywacja programu cieniującego
    //Przeslij parametry programu cieniującego do karty graficznej
    glUniformMatrix4fv(sp->u("P"),1,false,glm::value_ptr(P));
    glUniformMatrix4fv(sp->u("V"),1,false,glm::value_ptr(V));
    glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));

    glEnableVertexAttribArray(sp->a("vertex"));  //Włącz przesyłanie danych do atrybutu vertex
    glVertexAttribPointer(sp->a("vertex"),4,GL_FLOAT,false,0,vertices); //Wskaż tablicę z danymi dla atrybutu vertex

	glEnableVertexAttribArray(sp->a("color"));  //Włącz przesyłanie danych do atrybutu color
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, colors); //Wskaż tablicę z danymi dla atrybutu color

	glEnableVertexAttribArray(sp->a("normal"));  //Włącz przesyłanie danych do atrybutu normal
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, normals); //Wskaż tablicę z danymi dla atrybutu normal

	glEnableVertexAttribArray(sp->a("texCoord0"));  //Włącz przesyłanie danych do atrybutu normal
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords); //Wskaż tablicę z danymi dla atrybutu texCoord0

	// glUniform1i(sp->u("textureMap0"),0);
	glUniform1i(sp->u("textureMap1"),1);


	// glActiveTexture(GL_TEXTURE0);
	// glBindTexture(GL_TEXTURE_2D, tex0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex1);

    glDrawArrays(GL_TRIANGLES,0,vertexCount); //Narysuj obiekt

    glDisableVertexAttribArray(sp->a("vertex"));  //Wyłącz przesyłanie danych do atrybutu vertex
	glDisableVertexAttribArray(sp->a("color"));  //Wyłącz przesyłanie danych do atrybutu color
	glDisableVertexAttribArray(sp->a("normal"));  //Wyłącz przesyłanie danych do atrybutu normal
	glDisableVertexAttribArray(sp->a("texCoord0"));  //Wyłącz przesyłanie danych do atrybutu texCoord0

    glfwSwapBuffers(window); //Przerzuć tylny bufor na przedni
}


int main(void)
{
	GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(1280, 720, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

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
	float angle_x=0; //Aktualny kąt obrotu obiektu
	float angle_y=0; //Aktualny kąt obrotu obiektu

	
		

	// glfwSetTime(0); //Zeruj timer
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
        float currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		processInput(window);
		
        drawScene(window, camPos, camFront, camUp); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}

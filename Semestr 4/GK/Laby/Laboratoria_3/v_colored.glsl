#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

//Atrybuty
layout (location=0) in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
layout (location=3) in vec4 color; //kolor wierzcho³ka

out vec4 i_c;

void main(void) {
    i_c=color;
    gl_Position=P*V*M*vertex;
}

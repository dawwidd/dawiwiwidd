#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

//Atrybuty
in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec4 color;  //kolor związany z wierzchołkiem

//Zmienne interpolowane
out vec4 ic;


void main(void) {
    float d;
    vec4 a = vec4(0,5,0,1);

    d = distance(V*M*vertex, V * a);
    d = 1 - (d - 3.3) / 3.4;

    ic = vec4(color.rgb*d, color.a);
    gl_Position=P*V*M*vertex;
}

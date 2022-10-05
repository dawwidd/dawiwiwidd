#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

//Atrybuty
in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec4 color; //kolor związany z wierzchołkiem
in vec4 normal; //wektor normalny w przestrzeni modelu
in vec2 texCoord0;

//Zmienne interpolowane
out vec4 ic;
out vec4 l;
out vec4 n;
out vec4 v;
out vec2 itexCoord0;
out vec2 itexCoord1;

void main(void) {
    vec4 lp = vec4(0, 0, -6, 1); //pozcyja światła, przestrzeń świata
    l = normalize(V * lp - V*M*vertex); //wektor do światła w przestrzeni oka
    v = normalize(vec4(0, 0, 0, 1) - V * M * vertex); //wektor do obserwatora w przestrzeni oka
    n = normalize(V * M * normal); //wektor normalny w przestrzeni oka
    itexCoord0 = texCoord0;
    itexCoord1 = (n.xy + 1)/2;
    
    ic = color;
    
    gl_Position=P*V*M*vertex;
}

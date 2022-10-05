#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec4 lp;

//Atrybuty
in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec4 color;
in vec4 normal;


// Zm. interpolowane
out vec4 ic;
out vec4 l;
out vec4 n;
out vec4 v;

void main(void) {
    // vec4 lp=vec4(0,0,-6,1);     //przestrzeń świata

    l = normalize(V * lp - V*M*vertex);
    n = normalize(V * M * normal);
    // vec4 r = reflect(-l, n);
    v = normalize(vec4(0,0,0,1)-V * M * vertex);

    // float nl = clamp(dot(n, l), 0, 1);
    // float rv = pow(clamp(dot(r,v), 0, 1), 25);

    // ic = vec4(color.rgb * nl, color.a) + vec4(rv,rv,rv,0);


    gl_Position=P*V*M*vertex;
}

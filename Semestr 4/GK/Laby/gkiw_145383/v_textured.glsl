#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec4 lp1;
uniform vec4 lp2;
uniform vec4 lp3;
uniform vec4 lp4;
uniform vec4 lp5;


//Atrybuty
layout (location = 0) in vec4 vertex; // wspolrzedne wierzcholka w przestrzeni modelu
layout (location = 1) in vec4 normal;
layout (location = 2) in vec2 texCoord0;

//Zmienne interpolowane
out vec4 l1;
out vec4 l2;
out vec4 l3;
out vec4 l4;
out vec4 l5;
out vec4 n;
out vec4 v;
out vec2 itexCoord0;


void main(void) {
    //vec4 lp = vec4(0, 0, 6, 1); // źródło światła w przestrzeni świata

     l1 = normalize(V*lp1 - V*M*vertex); // wektor światła
     l2 = normalize(V*lp2 - V*M*vertex);
     l3 = normalize(V*lp3 - V*M*vertex);
     l4 = normalize(V*lp4 - V*M*vertex);
     l5 = normalize(V*lp5 - V*M*vertex);
     n = normalize(V*M*normal); // wektor normalny
     v = normalize(vec4(0,0,0,1) - V*M*vertex);

    itexCoord0 = texCoord0;

    gl_Position=P*V*M*vertex;






    
    //vec4 r = reflect(-l, n);    // wektor światła odbitego
    //ic = vec4(color.rgb*nl, color.a) + vec4(rv,rv,rv,0);
    //float nl = clamp(dot(n, l),0,1);
    //float rv = pow(clamp(dot(r, v), 0, 1), 25); // wektor skalarny r i v
    //float nl2 = clamp(dot(n, l2),0,1);
    //vec4 l2 = normalize(V*lp2 - V*M*vertex); // odległość wierzcholka od 2. źródła światła
}

#version 330

uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec4 l1;
in vec4 l2;
in vec4 l3;
in vec4 l4;
in vec4 l5;
in vec4 n;
in vec4 v;
in vec2 itexCoord0;

void main(void) {

	// Znormalizowane interpolowane wektory
	vec4 ml1 = normalize(l1);		// wektor światła
	vec4 ml2 = normalize(l2);		// wektor światła
	vec4 ml3 = normalize(l3);		// wektor światła
	vec4 ml4 = normalize(l4);		// wektor światła
	vec4 ml5 = normalize(l5);		// wektor światła
	vec4 mn = normalize(n);		// wektor normalny
	vec4 mv = normalize(v);		
	vec4 mr1 = reflect(-ml1, mn); // wektor odbity
	vec4 mr2 = reflect(-ml2, mn); // wektor odbity
	vec4 mr3 = reflect(-ml3, mn); // wektor odbity
	vec4 mr4 = reflect(-ml4, mn); // wektor odbity
	vec4 mr5 = reflect(-ml5, mn); // wektor odbity


	// Parametry powierzchni
	vec4 kd = texture(texture_diffuse, itexCoord0);
	vec4 ks = texture(texture_specular, itexCoord0);


	// Obliczenie modelu oświetlenia
	float nl1 = clamp(dot(mn, ml1),0,1);
	float nl2 = clamp(dot(mn, ml2),0,1);
	float nl3 = clamp(dot(mn, ml3),0,1);
	float nl4 = clamp(dot(mn, ml4),0,1);
	float nl5 = clamp(dot(mn, ml5),0,1);

    float rv1 = pow(clamp(dot(mr1, mv), 0, 1), 500);
    float rv2 = pow(clamp(dot(mr2, mv), 0, 1), 500);
    float rv3 = pow(clamp(dot(mr3, mv), 0, 1), 500);
    float rv4 = pow(clamp(dot(mr4, mv), 0, 1), 500);
    float rv5 = pow(clamp(dot(mr5, mv), 0, 1), 500);

	pixelColor = vec4(kd.rgb*nl1+kd.rgb*nl2+kd.rgb*nl3+kd.rgb*nl4+kd.rgb*nl5, ks.a) + vec4(kd.rgb*rv1+kd.rgb*rv2+kd.rgb*rv3+kd.rgb*rv4+kd.rgb*rv5,0);
}

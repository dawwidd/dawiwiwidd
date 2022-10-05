#version 330


out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela
in vec4 ic;
in vec4 l;
in vec4 n;
in vec4 v;

float toonify(float a, float s){
	return round(s*a)/s;
}


void main(void) {

	vec4 ml = normalize(l);
	vec4 mn = normalize(n);
	vec4 mv = normalize(v);
	vec4 mr = reflect(-ml, mn);


	float nl = clamp(dot(mn, ml), 0, 1);
    float rv = pow(clamp(dot(mr,mv), 0, 1), 25);

	//nl = toonify(nl,10);
	//rv = toonify(rv,10);

	pixelColor=vec4(ic.rgb * nl, ic.a) + vec4(rv,rv,rv,0);
}

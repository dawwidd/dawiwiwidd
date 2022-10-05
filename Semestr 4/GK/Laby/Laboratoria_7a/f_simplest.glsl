#version 330

uniform sampler2D textureMap0;
uniform sampler2D textureMap1;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec4 n;
in vec4 l;

in vec2 iTexCoord0;
in float layer;

void main(void) {

	//Znormalizowane interpolowane wektory
	vec4 ml = normalize(l);
	vec4 mn = normalize(n);

	//Obliczenie modelu oświetlenia
	float nl = clamp(dot(mn, ml), 0, 1);

	vec4 fur = texture(textureMap0, iTexCoord0);
	vec4 furCol = texture(textureMap1, iTexCoord0);
	vec4 col = furCol;

	if(layer != 0) col = vec4(furCol.rgb, fur.a);
	if(fur.a == 0 && layer != 0) discard;
	pixelColor = col * vec4(nl, nl, nl, 1);
}

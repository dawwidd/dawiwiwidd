#version 330

out vec4 pixelColor;
in vec4 iColor;

void main(void) {
	pixelColor = iColor;
}

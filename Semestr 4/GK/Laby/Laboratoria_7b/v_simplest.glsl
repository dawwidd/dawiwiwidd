#version 330


in vec4 vertex;
in vec4 color;

out vec4 gColor;
out vec4 gVertex;

void main(void) {
	gColor = color;
	gVertex = vertex;
}

#version 330

layout(triangles) in;
layout(line_strip) out;
layout(max_vertices = 6) out;

in vec4 gColor[];
out vec4 iColor;

void main(void) {
	int i;

	vec4 A = gl_in[0].gl_Position;
	vec4 B = gl_in[1].gl_Position;
	vec4 C = gl_in[2].gl_Position;

	vec4 cA = gColor[0];
	vec4 cB = gColor[1];
	vec4 cC = gColor[2];

	vec4 D = (A+B+C)/3;

	gl_Position = A;
	iColor = cA;
	EmitVertex();
	gl_Position = D;
	iColor = cA;
	EmitVertex();
	EndPrimitive();

	gl_Position = B;
	iColor = cB;
	EmitVertex();
	gl_Position = D;
	iColor = cB;
	EmitVertex();
	EndPrimitive();

	gl_Position = C;
	iColor = cC;
	EmitVertex();
	gl_Position = D;
	iColor = cC;
	EmitVertex();
	EndPrimitive();


	/*for (i = 0; i < gl_in.length(); i++) {
		gl_Position = gl_in[i].gl_Position;
		iColor = gColor[i];
		EmitVertex();
	}
	gl_Position = gl_in[0].gl_Position;
	iColor = gColor[0];
	EmitVertex();
	EndPrimitive();*/
}

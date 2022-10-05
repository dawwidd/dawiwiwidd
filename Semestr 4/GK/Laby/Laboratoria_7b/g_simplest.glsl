#version 330

layout(triangles) in;
layout(line_strip) out;
layout(max_vertices = 3) out;

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

uniform float amount;

in vec4 gVertex[];
in vec4 gColor[];
out vec4 iColor;

void main(void) {
	int i;

	vec3 a = (gVertex[1] - gVertex[0]).xyz;
	vec3 b = (gVertex[2] - gVertex[0]).xyz;

	vec4 n = vec4(normalize(cross(b,a)), 0);

	for(i = 0; i<gl_in.length(); i++){
		gl_Position = P*V*M*(gVertex[i] + amount * n);
		iColor = gColor[i];
		EmitVertex();
	}

	EndPrimitive();
}

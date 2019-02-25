// Version du GLSL

#version 410 core

layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

in float rand[3];
in vec2 vTexCoord[3];
in vec4 vNormal[3];
in vec4 vPos[3];

out vec2 gTexCoord;
out vec4 gNormal;
out vec4 gColor;
out vec4 gPos;


void main()
{
	float color;

	color = (fract(((1 + rand[0]) * (1 + rand[1]) * (1 + rand[2]))));
	gColor = vec4(color, color, color, 0);
	// gNormal = normalize(vec4(cross(normalize(vec3(vPos[0]) - vec3(vPos[1])), normalize(vec3(vPos[0]) - vec3(vPos[2]))), 0));
	gPos = (vPos[0] + vPos[1] + vPos[2]) / 3;
	gNormal = normalize((vNormal[0] + vNormal[1] + vNormal[2]) / 3);

	gl_Position = gl_in[0].gl_Position;
	gTexCoord = vTexCoord[0];
	EmitVertex();

	gl_Position = gl_in[1].gl_Position;
	gTexCoord = vTexCoord[1];
	EmitVertex();

	gl_Position = gl_in[2].gl_Position;
	gTexCoord = vTexCoord[2];
	EmitVertex();
	EndPrimitive();
}

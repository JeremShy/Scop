// Version du GLSL

#version 410 core

layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

in float tri[3];
in vec2 vTexCoord[3];
in vec3 vNormal[3];
in vec3 vFragPos[3];

out vec2 gTexCoord;
out vec3 gNormal;
out vec3 gFragPos;
out vec4 gColor;


void main()
{
	float color;

	color = (fract(((1 + tri[0]) * (1 + tri[1]) * (1 + tri[2]))));
    gColor = vec4(color, color, color, 0);
    gNormal =((vNormal[0] + vNormal[1] + vNormal[2]) * 1.0) / 3;
    gFragPos =((vFragPos[0] + vFragPos[1] + vFragPos[2]) * 1.0) / 3;

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

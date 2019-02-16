// Version du GLSL

#version 410 core

layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

in vec2 vTexCoord[3];
in float tri[3];
out vec2 gTexCoord;
out vec4 gColor;


void main()
{
	float color;

	color = (fract(((1 + tri[0]) * (1 + tri[1]) * (1 + tri[2]))));
    gColor = vec4(color, color, color, 0);

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

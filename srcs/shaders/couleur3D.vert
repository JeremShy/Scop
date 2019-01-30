// Version du GLSL

#version 410 core


// Entrées

layout (location = 0) in vec3 in_Vertex;
layout (location = 1) in vec3 in_Color;


// Uniform

uniform mat4 projection;
uniform mat4 modelview;


// Sortie

out vec3 color;


// Fonction main

void main()
{
    // Position finale du vertex en 3D
    gl_Position = projection * modelview * vec4(in_Vertex, 1.0);
    // gl_Position = projection * vec4(in_Vertex, 1.0);

	color = in_Color;
}

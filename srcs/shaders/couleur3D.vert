// Version du GLSL

#version 400 core


// Entrées

in vec3 in_Vertex;
in vec3 in_Color;


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

	color = in_Color;
}

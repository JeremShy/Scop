// Version du GLSL

#version 410 core


// Entrées

layout (location = 0) in vec3 in_Vertex;
layout (location = 1) in vec3 in_Color;
layout (location = 2) in vec2 aTexCoord;

// Sortie

uniform mat4 obj;

out vec2 texCoord;


// Fonction main

void main()
{
    // Position finale du vertex

    gl_Position = obj * vec4(in_Vertex, 1.0);


    // Envoi de la couleur au Fragment Shader

    texCoord = aTexCoord;
}

// Version du GLSL

#version 410 core


// Entr�e

in vec3 color;


// Sortie 

out vec4 out_Color;


// Fonction main

void main()
{
    // Couleur finale du pixel

    // out_Color = vec4(color, 1.0);
    out_Color = vec4(1.0, 1.0, 1.0, 1.0);
}

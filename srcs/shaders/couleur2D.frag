// Version du GLSL

#version 410 core


// Entrée

in vec2 texCoord;

uniform sampler2D tex;


// Sortie 

out vec4 out_Color;


// Fonction main

void main()
{
    // Couleur finale du pixel

    out_Color = texture(tex, texCoord);
   	// out_Color = vec4(1, 0, 0, 0);
}

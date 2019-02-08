// Version du GLSL

#version 410 core


// Entrée

in vec2 texCoord;

uniform sampler2D tex;
uniform int texOn;

// Sortie 

out vec4 out_Color;


// Fonction main

void main()
{
    // Couleur finale du pixel

    if (texOn == 0)
    	out_Color = texture(tex, texCoord);
   	else
   		out_Color = vec4(1, 1, 0, 0);
}

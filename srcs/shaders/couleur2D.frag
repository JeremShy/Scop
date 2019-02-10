// Version du GLSL

#version 410 core


// Entrée

in vec2 texCoord;
// in float color;
flat in vec4 color;

uniform sampler2D tex;
uniform int texOn;
// uniform int nb_face;

// in int gl_VertexID;in int gl_VertexID;
// in flat VertexID;
// Sortie 

out vec4 aColor;

// Fonction main

void main()
{
    // Couleur finale du pixel

    if (texOn == 1)
    	aColor = texture(tex, texCoord);
   	else
   		aColor = color;
   		// aColor = vec4(gl_PrimitiveID / (nb_face * 1.0), gl_PrimitiveID / (nb_face * 1.0), gl_PrimitiveID / (nb_face * 1.0), 0);
   		// aColor = vec4(gl_PrimitiveID / 2.0, gl_PrimitiveID / 2.0, gl_PrimitiveID / 2.0, 0);
}

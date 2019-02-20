// Version du GLSL

#version 410 core


// Entrées

layout (location = 0) in vec3 in_Vertex;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in float aColor;

// Sortie

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform bool defTex;

out float tri;
out vec2 vTexCoord;
out vec3 vNormal;

// Fonction main

void main()
{
    // Position finale du vertex

	gl_Position = projection * view * model * vec4(in_Vertex, 1.0);

    // Envoi de la couleur au Fragment Shader
	if (defTex)
	{
		vTexCoord.x = in_Vertex.y;
		vTexCoord.y = in_Vertex.z;
	}
	else
		vTexCoord = aTexCoord;
    tri = aColor;
    // color = (in_Vertex.x + in_Vertex.y + in_Vertex.z) / 3;
	// VertexID = gl_VertexID;
}

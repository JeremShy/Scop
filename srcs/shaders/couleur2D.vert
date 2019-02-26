// Version du GLSL

#version 410 core


// Entrées

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in float aRand;
layout (location = 3) in vec3 aNormal;

// Sortie

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform bool defTex;

out float rand;
out vec2 vTexCoord;
out vec4 vNormal;
out vec4 vPos;

// Fonction main

void main()
{
	// Position finale du vertex

	gl_Position = projection * view * model * vec4(aPos, 1.0);
	// Envoi de la couleur au Fragment Shader
	if (defTex)
	{
		vTexCoord.x = aPos.y;
		vTexCoord.y = aPos.z;
	}
	else
		vTexCoord = aTexCoord;
	rand = aRand;
	vNormal = normalize(model * vec4(normalize(aNormal), 0.0));
	vPos = model * vec4(aPos , 1);
	// color = (aPos.x + aPos.y + aPos.z) / 3;
	// VertexID = gl_VertexID;
}

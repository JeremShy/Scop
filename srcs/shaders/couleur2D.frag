// Version du GLSL

#version 410 core


// Entrée

in vec2 gTexCoord;
in vec3 gNormal;
in vec3 gFragPos;
in vec4 gColor;

uniform sampler2D tex;
uniform int texOn;
uniform float ambientStrength;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

// Sortie 

out vec4 aColor;

// Fonction main

void main()
{
	// ambient
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 norm = normalize(gNormal);
    vec3 lightDir = normalize(lightPos - gFragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - gFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  

    // Couleur finale du pixel
    if (texOn == 1)
    	aColor = texture(tex, gTexCoord) * vec4(ambient + diffuse + specular, 1.0);
   	else
   		aColor = gColor * vec4(ambient + diffuse + specular, 1.0);
   		// aColor = vec4(gl_PrimitiveID / (nb_face * 1.0), gl_PrimitiveID / (nb_face * 1.0), gl_PrimitiveID / (nb_face * 1.0), 0);
   		// aColor = vec4(gl_PrimitiveID / 2.0, gl_PrimitiveID / 2.0, gl_PrimitiveID / 2.0, 0);
}

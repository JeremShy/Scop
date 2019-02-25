// Version du GLSL

#version 410 core


// Entrée

in vec2 gTexCoord;
in vec4 gNormal;
in vec4 gColor;
in vec4 gPos;

uniform sampler2D tex;
uniform int texOn;
uniform float ambientStrength;
uniform vec4 lightPos;
uniform vec4 lightColor;
uniform vec4 viewPos;

// Sortie 

out vec4 aColor;

// Fonction main

void main()
{
	// ambient
    vec4 ambient = ambientStrength * lightColor;

    // diffuse
    vec4 norm = normalize(gNormal);
    vec4 lightDir = normalize(lightPos - gPos);
    // vec4 lightDir = normalize(lightPos - gl_FragCoord);
    float diff = dot(norm, lightDir);
    vec4 diffuse = lightColor * diff;

    // specular
    float specularStrength = 0.5;
    vec4 viewDir = normalize(viewPos - gPos);
    // vec4 viewDir = normalize(viewPos - gl_FragCoord);
    vec4 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec4 specular = specularStrength * spec * lightColor;  

    // Couleur finale du pixel
    if (texOn == 1)
    	aColor = texture(tex, gTexCoord) * (ambient + diffuse + specular);
   	else
   		aColor = gColor * (ambient + 0 + specular);
   		// aColor = vec4(gl_PrimitiveID / (nb_face * 1.0), gl_PrimitiveID / (nb_face * 1.0), gl_PrimitiveID / (nb_face * 1.0), 0);
   		// aColor = vec4(gl_PrimitiveID / 2.0, gl_PrimitiveID / 2.0, gl_PrimitiveID / 2.0, 0);
}

#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNormal;



uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


out vec3 LightingColor;


uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;

uniform float ambientStrength;
uniform float specularStrength;
uniform float diffuseStrength;
uniform int shininess;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);

vec3 FragPos = vec3(model * vec4(aPos, 1.0));
    // ambient
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = mat3(inverse(transpose(model))) * normalize(aNormal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff *diffuseStrength * lightColor;
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;  
        
    LightingColor = (ambient + diffuse + specular);
} 

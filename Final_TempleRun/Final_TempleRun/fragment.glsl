#version 330 core

in vec3 passColorAttribute;
in vec3 FragPos;
in vec3 Normal;
in mat4 trans;
in vec2 TexCoord;
out vec4 fragmentColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform float ambientLight;

uniform sampler2D outTexture;


void main()
{
    vec3 ambient = ambientLight * lightColor;

    vec3 normalVector = normalize(mat3(transpose(inverse(trans))) * Normal);
    vec3 lightDir = normalize((lightPos - FragPos));
    float diffuseLight = max(dot(normalVector, lightDir), 0.0);
    vec3 diffuse = diffuseLight * lightColor;

    int shininess = 128;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normalVector);
    float specularLight = max(dot(viewDir, reflectDir), 0.0);
    specularLight = pow(specularLight, shininess);
    vec3 specular = specularLight * lightColor;

    //vec3 result = (ambient + diffuse + specular) * objectColor;
    float dist = distance(lightPos, FragPos);
    vec3 result = ambient * objectColor + (diffuse + specular) * (objectColor / (dist * dist));

    fragmentColor = vec4(result, 0.5);
    fragmentColor = texture(outTexture, TexCoord) * fragmentColor;

}

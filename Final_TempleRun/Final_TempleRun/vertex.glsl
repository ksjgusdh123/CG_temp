#version 330 core

layout (location = 0) in vec3 positionAttribute;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;

out vec3 test;

out vec3 passColorAttribute;
out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoord;
out mat4 trans;
uniform mat4 transform;		
uniform mat4 viewTransform;		
uniform mat4 projectionTransform;		
uniform vec3 colorAttribute;
	
void main()
{
	gl_Position = projectionTransform * viewTransform* transform * vec4(positionAttribute, 1.0); 
	passColorAttribute = colorAttribute;

	FragPos = vec3(transform * vec4(positionAttribute, 1.0));
	trans = transform;
	Normal = vNormal;
	TexCoord = vTexCoord;

	test = positionAttribute;
};
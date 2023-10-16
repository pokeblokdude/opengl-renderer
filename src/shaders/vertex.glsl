#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
//layout (location = 1) in vec3 aColor;

uniform mat4 MV;
uniform mat4 view;
//uniform mat4 projection;

uniform mat4 MVP;
uniform vec3 camVector;

//out vec3 ourColor;
out vec3 pos;
out vec3 normal;
out vec2 texCoord;
out vec3 cam;

void main()
{
	pos = aPos;
	gl_Position = MVP * vec4(aPos, 1.0);
	mat3 normMatrix = transpose(inverse(mat3(MV)));
	normal = normalize(normMatrix * aNormal);
	//ourColor = aColor;
	texCoord = aTexCoord;
	cam = -normalize((view * vec4(camVector, 1.0f)).xyz);
}
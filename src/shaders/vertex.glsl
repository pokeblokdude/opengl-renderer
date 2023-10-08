#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
//layout (location = 1) in vec3 aColor;

//uniform mat4 transform;
//uniform mat4 view;
//uniform mat4 projection;

uniform mat4 MVP;

//out vec3 ourColor;
//out vec3 pos;
out vec2 texCoord;

void main()
{
	//pos = aPos;
	gl_Position = MVP * vec4(aPos, 1.0);
	//ourColor = aColor;
	texCoord = aTexCoord;
}
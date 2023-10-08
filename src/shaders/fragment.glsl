#version 410 core

out vec4 FragColor;
//in vec3 ourColor;
//in vec3 pos;
in vec2 texCoord;

//iform float blend = 0.5f;

uniform sampler2D tex;
//iform sampler2D tex2;

void main()
{
	FragColor = texture2D(tex, texCoord) * vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
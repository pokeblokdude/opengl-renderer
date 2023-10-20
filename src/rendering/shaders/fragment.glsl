#version 410 core

out vec4 FragColor;
//in vec3 ourColor;
in vec3 pos;
in vec3 normal;
in vec2 texCoord;
in vec3 cam;

//iform float blend = 0.5f;
uniform sampler2D texture_diffuse0;
//iform sampler2D tex2;

void main()
{
	vec3 ambient = vec3(0.05f, 0.05f, 0.05f);
	vec4 color = texture2D(texture_diffuse0, texCoord) * vec4(1.0f, 1.0f, 1.0f, 1.0f);

	color = color * clamp(dot(cam, normal), 0, 1);
	
	FragColor = color + vec4(ambient, 0);
	//FragColor = vec4(1, 1, 1, 1);
}
#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <string>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

struct Texture {
	uint32_t id;
	std::string type;
	std::string path;
};

struct Material {
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 ambient;
	float shininess;
};

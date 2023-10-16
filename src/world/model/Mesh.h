#pragma once

#include <glm/vec3.hpp>
#include <vector>
#include <string>
#include "../Object.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

struct Texture {
	uint32_t id;
	std::string type;
};

class Mesh {

public:
	~Mesh();

	std::vector<Vertex> verts;
	std::vector<uint32_t> faces;

	uint32_t VertexArrayObject();

protected:
	void GenBuffers();

private:
	uint32_t VAO, VBO, EBO;	

};


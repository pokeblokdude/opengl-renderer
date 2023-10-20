#pragma once

#include <glm/vec3.hpp>
#include <vector>
#include <string>
#include "primitives/PrimitiveShape.h"
#include "../Object.h"
#include <iostream>

class Mesh {

public:
	Mesh(PrimitiveShape& shape);
	Mesh(std::vector<struct Vertex> verts, std::vector<uint32_t> indicies, std::vector<struct Texture> textures);

	~Mesh();

	std::vector<Vertex> verts;
	std::vector<uint32_t> indicies;
	std::vector<Texture> textures;

	void Draw(class Shader& shader);

protected:
	void GenBuffers();

private:
	uint32_t VAO, VBO, EBO;	

};


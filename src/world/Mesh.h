#pragma once

#include <vector>
#include "Object.h"

class Mesh {

public:
	~Mesh();

	std::vector<float> verts;
	std::vector<uint32_t> faces;

	uint32_t VertexArrayObject();

protected:
	void GenBuffers();

private:
	uint32_t VAO, VBO, EBO;	

};


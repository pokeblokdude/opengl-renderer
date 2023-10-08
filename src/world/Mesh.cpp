#include <glad/glad.h>
#include "Mesh.h"

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

uint32_t Mesh::VertexArrayObject() {
	return VAO;
}

void Mesh::GenBuffers() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	// GL_STATIC_DRAW - vertex data is set once and used many times
	// GL_DYNAMIC_DRAW - vertex data is changed a lot and used many times
	// GL_STREAM_DRAW - vertex data is set once and used few times

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(uint32_t), faces.data(), GL_STATIC_DRAW);

	// glVertexAttribPointer:
	// - index (in order of attributes, vertex shader "layout"): int
	// - count (number of elements/floats): int
	// - data type (probably GL_FLOAT): openGL data type enum
	// - normalized (idk, GL_FALSE): openGL bool enum
	// - stride (number of bytes between data start, ie full size of vertex in bytes): int
	// - offset (number of bytes in vertex before data start): (void*)int

	// specify vertex attribute layout
	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	// UVs
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
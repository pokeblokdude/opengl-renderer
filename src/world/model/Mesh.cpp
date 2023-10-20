#include <glad/glad.h>
#include "../../rendering/Shader.h"
#include <string>
#include "Mesh.h"

Mesh::Mesh(PrimitiveShape& shape) {
	this->verts = shape.verts;
	this->indicies = shape.indicies;
}
Mesh::Mesh(std::vector<struct Vertex> verts, std::vector<uint32_t> indicies, std::vector<struct Texture> textures) {
	this->verts = verts;
	this->indicies = indicies;
	this->textures = textures;

	std::cout << "Creating new mesh:" << std::endl;
	std::cout << "Verts: " << verts.size() << std::endl;
	std::cout << "Faces: " << indicies.size()/3.0f << std::endl;
	std::cout << "Textures: " << textures.size() << std::endl;

	GenBuffers();
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Mesh::Draw(Shader& shader) {
	uint32_t diffuseN = 1, specularN = 1;
	for (int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);

		std::string number;
		std::string name = textures[i].type;
		if (name == "texture_diffuse") {
			number = std::to_string(diffuseN);
			diffuseN++;
		}
		else if(name == "texture_specular") {
			number = std::to_string(specularN);
			specularN++;
		}

		shader.SetInt(("material." + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);

	std::cout << "Drawing mesh " << this << std::endl;
	std::cout << verts.size() << " verts" << std::endl;
	std::cout << indicies.size() << " indicies" << std::endl;
	std::cout << indicies.size()/3.0f << " faces" << std::endl;
	std::cout << textures.size() << " textures" << std::endl;

	// draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
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
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vertex), verts.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(uint32_t), indicies.data(), GL_STATIC_DRAW);

	// glVertexAttribPointer:
	// - index (in order of attributes, vertex shader "layout"): int
	// - count (number of elements/floats): int
	// - data type (probably GL_FLOAT): openGL data type enum
	// - normalized (idk, GL_FALSE): openGL bool enum
	// - stride (number of bytes between data start, ie full size of vertex in bytes): int
	// - offset (number of bytes in vertex before data start): (void*)int

	// specify vertex attribute layout
	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	// normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);
	// UVs
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
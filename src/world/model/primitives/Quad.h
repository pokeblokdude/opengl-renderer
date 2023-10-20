#pragma once

#include "PrimitiveShape.h"

class Quad : public PrimitiveShape {

public:
	
	Quad() {
		verts = {
		// VERTEX - Position - - - - - - - - - - | Normals - - - - - - - - - - - | UV Coords - - - - - - 
			Vertex{ glm::vec3{-0.5f, -0.5f, 0.0f }, glm::vec3{ 0.0f, 0.0f, 1.0f }, glm::vec2{ 0.0f, 0.0f } },	// bottom left
			Vertex{ glm::vec3{ 0.5f, -0.5f, 0.0f }, glm::vec3{ 0.0f, 0.0f, 1.0f }, glm::vec2{ 1.0f, 0.0f } },	// bottom right
			Vertex{ glm::vec3{-0.5f,  0.5f, 0.0f }, glm::vec3{ 0.0f, 0.0f, 1.0f }, glm::vec2{ 0.0f, 1.0f } },	// top left
			Vertex{ glm::vec3{ 0.5f,  0.5f, 0.0f }, glm::vec3{ 0.0f, 0.0f, 1.0f }, glm::vec2{ 1.0f, 1.0f } },	// top right
		};
		indicies = {
			0, 3, 2,
			0, 1, 3,
		};
	}

};


#pragma once

#include "../Mesh.h"

class Cube : public Mesh {

public:
	Cube() {
		// TODO: fix broken uv coords on top & bottom faces (need split vertices)
		verts = {
		// VERTEX - Position - - - - - - - - - - - | Normal - - - - - - - - - - - | UV Coords - 
			// BACK FACE
			Vertex{ glm::vec3{ 0.5f,  0.5f, -0.5f }, glm::vec3{ 0.0f, 0.0f, -1.0f }, glm::vec2{ 0.0f, 1.0f } },	// 0 - back top right
			Vertex{ glm::vec3{-0.5f,  0.5f, -0.5f }, glm::vec3{ 0.0f, 0.0f, -1.0f }, glm::vec2{ 1.0f, 1.0f } },	// 1 - back top left
			Vertex{ glm::vec3{-0.5f, -0.5f, -0.5f }, glm::vec3{ 0.0f, 0.0f, -1.0f }, glm::vec2{ 1.0f, 0.0f } },	// 2 - back bottom left
			Vertex{ glm::vec3{ 0.5f, -0.5f, -0.5f }, glm::vec3{ 0.0f, 0.0f, -1.0f }, glm::vec2{ 0.0f, 0.0f } },	// 3 - back bottom right
			// FRONT FACE
			Vertex{ glm::vec3{ 0.5f,  0.5f,  0.5f }, glm::vec3{ 0.0f, 0.0f, 1.0f }, glm::vec2{ 1.0f, 1.0f } },	// 4 - front top right
			Vertex{ glm::vec3{-0.5f,  0.5f,  0.5f }, glm::vec3{ 0.0f, 0.0f, 1.0f }, glm::vec2{ 0.0f, 1.0f } },	// 5 - front top left
			Vertex{ glm::vec3{-0.5f, -0.5f,  0.5f }, glm::vec3{ 0.0f, 0.0f, 1.0f }, glm::vec2{ 0.0f, 0.0f } },	// 6 - front bottom left
			Vertex{ glm::vec3{ 0.5f, -0.5f,  0.5f }, glm::vec3{ 0.0f, 0.0f, 1.0f }, glm::vec2{ 1.0f, 0.0f } },	// 7 - front bottom right
			// LEFT FACE
			Vertex{ glm::vec3{-0.5f,  0.5f,  0.5f }, glm::vec3{-1.0f, 0.0f, 0.0f }, glm::vec2{ 1.0f, 1.0f } },	// 8 - front top left
			Vertex{ glm::vec3{-0.5f,  0.5f, -0.5f }, glm::vec3{-1.0f, 0.0f, 0.0f }, glm::vec2{ 0.0f, 1.0f } },	// 9 - back top left
			Vertex{ glm::vec3{-0.5f, -0.5f, -0.5f }, glm::vec3{-1.0f, 0.0f,	0.0f }, glm::vec2{ 0.0f, 0.0f } },	// 10 - back bottom left
			Vertex{ glm::vec3{-0.5f, -0.5f,  0.5f }, glm::vec3{-1.0f, 0.0f, 0.0f }, glm::vec2{ 1.0f, 0.0f } },	// 11 - front bottom left
			// RIGHT FACE
			Vertex{ glm::vec3{ 0.5f,  0.5f,  0.5f }, glm::vec3{ 1.0f, 0.0f, 0.0f }, glm::vec2{ 0.0f, 1.0f } },	// 12 - front top right
			Vertex{ glm::vec3{ 0.5f,  0.5f, -0.5f }, glm::vec3{ 1.0f, 0.0f, 0.0f }, glm::vec2{ 1.0f, 1.0f } },	// 13 - back top right
			Vertex{ glm::vec3{ 0.5f, -0.5f, -0.5f }, glm::vec3{ 1.0f, 0.0f, 0.0f }, glm::vec2{ 1.0f, 0.0f } },	// 14 - back bottom right
			Vertex{ glm::vec3{ 0.5f, -0.5f,  0.5f }, glm::vec3{ 1.0f, 0.0f, 0.0f }, glm::vec2{ 0.0f, 0.0f } },	// 15 - front bottom right
			// TOP FACE
			Vertex{ glm::vec3{-0.5f,  0.5f,  0.5f }, glm::vec3{ 0.0f, 1.0f, 0.0f }, glm::vec2{ 0.0f, 0.0f } },	// 16 - front top left
			Vertex{ glm::vec3{ 0.5f,  0.5f,  0.5f }, glm::vec3{ 0.0f, 1.0f, 0.0f }, glm::vec2{ 1.0f, 0.0f } },	// 17 - front top right
			Vertex{ glm::vec3{ 0.5f,  0.5f, -0.5f }, glm::vec3{ 0.0f, 1.0f, 0.0f }, glm::vec2{ 1.0f, 1.0f } },	// 18 - back top right
			Vertex{ glm::vec3{-0.5f,  0.5f, -0.5f }, glm::vec3{ 0.0f, 1.0f, 0.0f }, glm::vec2{ 0.0f, 1.0f } },	// 19 - back top left
			// BOTTOM FACE
			Vertex{ glm::vec3{-0.5f, -0.5f,  0.5f }, glm::vec3{ 0.0f, -1.0f, 0.0f }, glm::vec2{ 0.0f, 1.0f } },	// 20 - front bottom left
			Vertex{ glm::vec3{ 0.5f, -0.5f,  0.5f }, glm::vec3{ 0.0f, -1.0f, 0.0f }, glm::vec2{ 1.0f, 1.0f } },	// 21 - front bottom right
			Vertex{ glm::vec3{ 0.5f, -0.5f, -0.5f }, glm::vec3{ 0.0f, -1.0f, 0.0f }, glm::vec2{ 1.0f, 0.0f } },	// 22 - back bottom right
			Vertex{ glm::vec3{-0.5f, -0.5f, -0.5f }, glm::vec3{ 0.0f, -1.0f, 0.0f }, glm::vec2{ 0.0f, 0.0f } },	// 23 - back bottom left
		};
		faces = {
			 1,  0,  2, // back 1
			 0,  3,  2, // back 2
			 4,  6,  7, // front 1
			 4,  5,  6, // front 2
			 8, 10, 11, // left 1
			 9, 10,  8, // left 2
			12, 14, 13, // right 1
			12, 15, 14, // right 2
			17, 18, 19, // top 1
			17, 19, 16, // top 2
			23, 22, 21, // bottom 1
			21, 20, 23, // bottom 2
		};

		GenBuffers();
	}

};


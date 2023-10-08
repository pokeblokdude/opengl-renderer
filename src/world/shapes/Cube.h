#pragma once

#include "../Mesh.h"

class Cube : public Mesh {

public:
	Cube() {
		verts = {
			 0.5f,  0.5f, -0.5f, 0.0f, 1.0f,		// 0 - back top right
			-0.5f,  0.5f, -0.5f, 1.0f, 1.0f,		// 1 - back top left
			-0.5f, -0.5f, -0.5f, 1.0f, 0.0f,		// 2 - back bottom left
			 0.5f, -0.5f, -0.5f, 0.0f, 0.0f,		// 3 - back bottom right
			 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,		// 4 - front top right
			-0.5f,  0.5f,  0.5f, 0.0f, 1.0f,		// 5 - front top left
			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,		// 6 - front bottom left
			 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,		// 7 - front bottom right
		};
		faces = {
			0, 1, 2,
			0, 2, 3,
			0, 4, 1,
			4, 5, 1,
			1, 5, 6,
			1, 6, 2,
			4, 3, 7,
			4, 0, 3,
			3, 2, 6,
			3, 6, 7,
			5, 4, 7,
			5, 7, 6,
		};

		GenBuffers();
	}

};


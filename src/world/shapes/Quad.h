#pragma once

#include "../Mesh.h"

class Quad : public Mesh {

public:
	Quad() {
		verts = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,		// bottom left
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,		// bottom right
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,		// top left
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,		// top right
		};
		faces = {
			0, 3, 2,
			0, 1, 3,
		};

		GenBuffers();
	}

};


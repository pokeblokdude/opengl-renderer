#pragma once

#include "../Mesh.h"

class Cube : public Mesh {

public:
	Cube() {
		verts = {
			 0.5f,  0.5f, -0.5f,		// 0 - front top right
			-0.5f,  0.5f, -0.5f,		// 1 - front top left
			-0.5f, -0.5f, -0.5f,		// 2 - front bottom left
			 0.5f, -0.5f, -0.5f,		// 3 - front bottom right
			 0.5f,  0.5f,  0.5f,		// 4 - back top right
			-0.5f,  0.5f,  0.5f,		// 5 - back top left
			-0.5f, -0.5f,  0.5f,		// 6 - back bottom right
			 0.5f, -0.5f,  0.5f,		// 7 - back bottom left
		};
		faces = {
			0, 1, 2,	// front
			0, 2, 3,	//
			0, 4, 1,	// top
			4, 5, 1,	//
			1, 5, 6,	// left
			1, 6, 2,	//
			4, 3, 7,	// right
			4, 0, 3,	//
			3, 2, 6,	// bottom
			3, 6, 7,	//
			5, 4, 7,	// back
			5, 7, 6		//
		};

		GenBuffers();
	}

};


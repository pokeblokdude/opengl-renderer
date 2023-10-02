#pragma once

#include "Object.h"
#include <glm/matrix.hpp>

class Camera : public Object {

public:

	float fov = 50;
	float aspect;
	float nearClip = 0.001f;
	float farClip = 1000;

	Camera(float fov, float aspect, float near, float far);

	glm::mat4 ProjectionMatrix();
	glm::mat4 ViewMatrix();

	void Resize(float aspect);

};


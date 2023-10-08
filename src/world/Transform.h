#pragma once
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

class Transform {

public:
	glm::vec3 position = { 0, 0, 0 };
	glm::vec3 scale = { 1, 1, 1 };
	glm::vec3 rotation = { 0, 0, 0 };

	glm::mat4 Matrix();

	glm::vec3 Forward();
	glm::vec3 Right();
	glm::vec3 Up();

};


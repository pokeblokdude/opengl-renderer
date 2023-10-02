#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Transform::Matrix() {
	glm::mat4 mat(1.0f);
	mat = glm::translate(mat, position);
	mat = glm::rotate(mat, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	mat = glm::rotate(mat, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	mat = glm::rotate(mat, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	mat = glm::scale(mat, scale);

	return mat;
}

glm::vec3 Transform::Forward() {
	glm::vec3 forward(
		glm::cos(rotation.x) * glm::sin(rotation.y),
		-glm::sin(rotation.x),
		glm::cos(rotation.x) * glm::cos(rotation.y)
	);
	return forward;
}

glm::vec3 Transform::Right() {
	return glm::vec3(
		//glm::cos(rotation.y),
		//0;
	);
}
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
	return glm::vec3(
		glm::cos(glm::radians(rotation.x)) * glm::sin(glm::radians(rotation.y)),
		-glm::sin(glm::radians(rotation.x)),
		glm::cos(glm::radians(rotation.x)) * -glm::cos(glm::radians(rotation.y))
	);
}

glm::vec3 Transform::Right() {
	return glm::cross(Forward(), glm::vec3(0, 1, 0));
}

glm::vec3 Transform::Up() {
	return glm::cross(Right(), Forward());
}